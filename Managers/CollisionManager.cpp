#include "pch.h"
#include "CollisionManager.h"

#include "..//Objects//Components//Body.h"
#include "..//Objects//Components//Shapes.h"


// Collision Functions
// NO STATIC V STATIC COLLISIONS
// Not needed due to the fact that two static objects don't collide or create a wall

/// The for(; time < 1.0f; time += 0.1) loop is used
/// due to the lack of formulas that can calculate timed OBB dynamic collisions
/// these are static checks at each moment of time per frame


/// checks if an animated sphere going from spSt1 to spEn1 with radius1
/// collides with the sphere with center spCen2 and with radius2
/// and returns the time when the collision happens
/// or -1 if it doesn't
float AnimatedSphereVSSphere(glm::vec3& spSt1, glm::vec3& spEn1, float radius1,
	glm::vec3& spCen2, float radius2)
{
	glm::vec3 spDir1 = spEn1 - spSt1;
	glm::vec3 spDir1N = spDir1;
	spDir1N = glm::normalize(spDir1N);
	glm::vec3 spSp12 = spCen2 - spSt1;

	float dotProd = glm::dot(spDir1N, spSp12);
	float lenProd = static_cast<double>(glm::length(spDir1)) * static_cast<double>(glm::length(spSp12));

	if (dotProd < 0.0f && glm::length(spSp12) > radius1 + radius2)
	{
		return -1.0f;
	}

	if (glm::dot(spSp12, spSp12) - dotProd * dotProd > (radius1 + radius2) * (radius1 + radius2))
	{
		return -1.0f;
	}

	float s = std::sqrt(glm::dot(spSp12, spSp12) - dotProd * dotProd);

	float spDir1L = glm::length(spDir1);

	float time = (dotProd - s) / spDir1L;

	if (time < 0.0f || time > 1.0f)
	{
		return -1.0f;
	}

	return time;
}

/// Takes b1 and b2 bodies with Sphere shapes
/// and std::vector of contacts that contains all the contacts at this frame
/// checks what type of contact to create => dynamic v dynamic or dynamic v static
void CollideSphereVSphere(Body* b1, Body* b2, std::vector<Contact*>& contacts)
{
	bool moveB1 = b1->GetMove();
	bool moveB2 = b2->GetMove();

	float time = 0.0f;

	if (true == moveB1 && true == moveB2)
	{
		float rad1 = dynamic_cast<Sphere*>(b1->GetShape())->GetRadius();
		float rad2 = dynamic_cast<Sphere*>(b2->GetShape())->GetRadius();

		glm::vec3 startPoint1 = b1->position;
		glm::vec3 endPoint1 = b1->nextPosition;

		glm::vec3 startPoint2 = b2->position;
		glm::vec3 endPoint2 = b2->nextPosition;

		// if the bodies haven't moved yet => no collision registration
		if (startPoint1 == endPoint1 || startPoint2 == endPoint2)
		{
			return;
		}

		startPoint1 += endPoint2 - startPoint2;

		time = AnimatedSphereVSSphere(startPoint1, endPoint1, rad1, endPoint2, rad2);
		
		if (-1.0f != time)
		{
			Contact* contact = new Contact();
			contact->SetBodies(b1, b2);
			contact->SetTime(time);
			contact->SetType(ContactType::TYPE_DYNAMIC_V_DYNAMIC);
			contacts.push_back(contact);
		}
	}
	else if (true == moveB1)
	{
		float rad1 = dynamic_cast<Sphere*>(b1->GetShape())->GetRadius();
		float rad2 = dynamic_cast<Sphere*>(b2->GetShape())->GetRadius();

		glm::vec3 startPoint1 = b1->position;
		glm::vec3 endPoint1 = b1->nextPosition;
		glm::vec3 endPoint2 = b2->nextPosition;

		// if the bodies haven't moved yet => no collision registration
		if (startPoint1 == endPoint1)
		{
			return;
		}

		time = AnimatedSphereVSSphere(startPoint1, endPoint1, rad1, endPoint2, rad2);

		if (-1.0f != time)
		{
			Contact* contact = new Contact();
			contact->SetBodies(b1, b2);
			contact->SetTime(time);
			contact->SetType(ContactType::TYPE_DYNAMIC_V_STATIC);
			contacts.push_back(contact);
		}
	}
	else if (true == moveB2)
	{
		float rad1 = dynamic_cast<Sphere*>(b1->GetShape())->GetRadius();
		float rad2 = dynamic_cast<Sphere*>(b2->GetShape())->GetRadius();

		glm::vec3 endPoint1 = b1->nextPosition;
		glm::vec3 startPoint2 = b2->position;
		glm::vec3 endPoint2 = b2->nextPosition;

		// if the bodies haven't moved yet => no collision registration
		if (startPoint2 == endPoint2)
		{
			return;
		}

		time = AnimatedSphereVSSphere(startPoint2, endPoint2, rad2, endPoint1, rad1);
		
		if (-1.0f != time)
		{
			Contact* contact = new Contact();
			contact->SetBodies(b2, b1);
			contact->SetTime(time);
			contact->SetType(ContactType::TYPE_DYNAMIC_V_STATIC);
			contacts.push_back(contact);
		}
	}
}

/// Takes W/move vector and D/centers vector
/// params --- parameters for each OBB that contain full height, length, and width values
/// norms --- normal vectors for the OBB faces that correspond accordingly with params
/// Implementation of the algorythm found in the paper:
/// https://www.geometrictools.com/Documentation/DynamicCollisionDetection.pdf
bool AnimatedOBBVSOBB(
	glm::vec3 W, glm::vec3 D,
	float (*params1)[3],
	std::vector<glm::vec3>& norms1,						// params[i] <=> norms[i], 0 - height/top, 1 - length/front, 2 - width/side
	float (*params2)[3],
	std::vector<glm::vec3>& norms2
)
{
	glm::mat3 A(norms1[0], norms1[1], norms1[2]);
	glm::mat3 B(norms2[0], norms2[1], norms2[2]);

	glm::transpose(A);

	glm::mat3 C = A * B;

	float alpha[3]	= { 0.0f, 0.0f, 0.0f };
	float beta[3]	= { 0.0f, 0.0f, 0.0f };

	for (size_t i = 0; i < 3; ++i)
	{
		alpha[i]	= glm::dot(W, norms1[i]);
		beta[i]		= glm::dot(W, norms2[i]);
	}

	for (size_t i = 0; i < 3; ++i)
	{
		float AiWD = glm::dot(norms1[i], glm::cross(W, norms1[i]));
		float BiWD = glm::dot(norms2[i], glm::cross(W, norms2[i]));

		float R = std::abs(glm::dot(norms1[0], D));
		float R0 = (*params1)[i];
		float R1 = (*params2)[0] * std::abs(C[0][i]) + (*params2)[1] * std::abs(C[1][i]) + (*params2)[2] * std::abs(C[2][i]);

		if (R > R0 + R1)
			return false;

		R = std::abs(glm::dot(norms2[0], D));
		R0 = (*params2)[i];
		R1 = (*params1)[0] * std::abs(C[i][0]) + (*params2)[1] * std::abs(C[i][1]) + (*params2)[2] * std::abs(C[i][2]);

		if (R > R0 + R1)
			return false;

		R0 = (*params1)[(i + 1) % 3] * std::abs(alpha[(i + 2) % 3]) + (*params1)[(i + 2) % 3] * std::abs(alpha[(i + 1) % 3]);
		R1 = 0.0f;
		for (size_t j = 0; j < 3; ++j)
		{
			R1 += (*params2)[i] * std::abs(C[(i + 1) % 3][j] * alpha[(i + 2) % 3] - C[(i + 2) % 3][j] * alpha[(i + 1) % 3]);
		}

		if (R > R0 + R1)
			return false;

		R0 = (*params2)[(i + 1) % 3] * std::abs(beta[(i + 2) % 3]) + (*params2)[(i + 2) % 3] * std::abs(beta[(i + 1) % 3]);
		R1 = 0.0f;
		for (size_t j = 0; j < 3; ++j)
		{
			R1 += (*params1)[i] * std::abs(C[j][(i + 1) % 3] * alpha[(i + 2) % 3] - C[j][(i + 2) % 3] * alpha[(i + 1) % 3]);
		}

		if (R > R0 + R1)
			return false;
	}

	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			glm::vec3 AiBj = glm::cross(norms1[i], norms2[j]);

			float R = std::abs(C[(i + 1) % 3][j] * glm::dot(norms1[(i + 2) % 3], D) - C[(i + 2) % 3][j] * glm::dot(norms1[(i + 1) % 3], D));
			float R0 = (*params1)[(i + 1) % 3] * std::abs(C[(i + 2) % 3][j]) + (*params1)[(i + 2) % 3] * std::abs(C[(i + 1) % 3][j]);
			float R1 = (*params2)[(j + 1) % 3] * std::abs(C[i][(j + 2) % 3]) + (*params2)[(j + 2) % 3] * std::abs(C[i][(j + 1) % 3]);

			if (R > R0 + R1)
				return false;
		}
	}

	return true;
}

/// Takes b1 and b2 bodies with OBB shapes
/// and std::vector of contacts that contains all the contacts at this frame
/// checks what type of contact to create => dynamic v dynamic or dynamic v static
void CollideOBBVSOBB(Body* b1, Body* b2, std::vector<Contact*>& contacts)
{
	bool moveB1 = b1->GetMove();
	bool moveB2 = b2->GetMove();

	OBB* obb1 = dynamic_cast<OBB*>(b1->GetShape());
	OBB* obb2 = dynamic_cast<OBB*>(b2->GetShape());

	float time = 0.0f;

	if (true == moveB1 && true == moveB2)
	{
		// if the bodies haven't moved yet => no collision registration
		if (b1->nextPosition == b1->nextPosition || b2->nextPosition == b2->position)
		{
			return;
		}

		glm::vec3 W = (b1->nextPosition - b1->position) - (b2->nextPosition - b2->position);

		for (; time < 1.0f; time += 0.1)
		{
			glm::vec3 D = b2->position - (b1->position + (time * W));

			if (true == AnimatedOBBVSOBB(W, D, &(obb1->params), obb1->GetNormals(), &(obb2->params), obb2->GetNormals()))
			{
				Contact* contact = new Contact();
				contact->SetBodies(b1, b2);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_DYNAMIC);
				contacts.push_back(contact);
				return;
			}
		}
	}
	else if (true == moveB1)
	{
		// if the bodies haven't moved yet => no collision registration
		if (b1->nextPosition == b1->nextPosition)
		{
			return;
		}

		glm::vec3 W = b1->nextPosition - b1->position;

		for (; time < 1.0f; time += 0.1)
		{
			glm::vec3 D = b2->nextPosition - (b1->position + (time * W));

			if (true == AnimatedOBBVSOBB(W, D, &(obb1->params), obb1->GetNormals(), &(obb2->params), obb2->GetNormals()))
			{
				Contact* contact = new Contact();
				contact->SetBodies(b1, b2);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_STATIC);
				contacts.push_back(contact);
				return;
			}
		}
	}
	else if (true == moveB2)
	{
		// if the bodies haven't moved yet => no collision registration
		if (b2->nextPosition == b2->position)
		{
			return;
		}

		glm::vec3 W = b2->nextPosition - b2->position;

		for (; time < 1.0f; time += 0.1)
		{
			glm::vec3 D = b1->nextPosition - (b2->position + (time * W));

			if (true == AnimatedOBBVSOBB(W, D, &(obb2->params), obb2->GetNormals(), &(obb1->params), obb1->GetNormals()))
			{
				Contact* contact = new Contact();
				contact->SetBodies(b2, b1);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_STATIC);
				contacts.push_back(contact);
				return;
			}
		}
	}
}


/// Takes the vector from the point to the center of OBB
/// params and norms of the OBB as described in AnimatedOBBVSOBB description
bool PointInOBB(glm::vec3 fromPointToCen,
	float params[3],
	std::vector<glm::vec3>& norms)
{
	float dist = glm::length(fromPointToCen);

	if (std::abs(glm::dot(norms[0], fromPointToCen)) <= params[0] / 2.0f
		&&
		std::abs(glm::dot(norms[1], fromPointToCen)) <= params[1] / 2.0f
		&&
		std::abs(glm::dot(norms[2], fromPointToCen)) <= params[2] / 2.0f)
	{
		return true;
	}

	return false;
}

/// Takes b1 and b2 bodies with Sphere and OBB shapes respectively
/// and std::vector of contacts that contains all the contacts at this frame
/// checks what type of contact to create => dynamic v dynamic or dynamic v static
void CollideSphereVSOBB(Body* b1, Body* b2, std::vector<Contact*>& contacts)
{
	bool moveB1 = b1->GetMove();
	bool moveB2 = b2->GetMove();

	float time = 0.0f;

	float rad1 = dynamic_cast<Sphere*>(b1->GetShape())->GetRadius();
	std::vector<glm::vec3> obbVerts;

	std::vector<glm::vec3>& norms = dynamic_cast<OBB*>(b2->GetShape())->GetNormals();

	float updParams[3];
	for (size_t i = 0; i < 3; ++i)
	{
		updParams[i] = dynamic_cast<OBB*>(b2->GetShape())->params[i] + 2.0f * rad1;
	}

	glm::vec3 obbPos = b2->nextPosition;

	/// Create a Vector of the OBB vertices to check for vertex collisions
	int addi = -1;
	for (size_t i = 0; i < 2; ++i)
	{
		glm::vec3 hNorm = float(addi) * dynamic_cast<OBB*>(b2->GetShape())->params[0] / 2.0f * (norms[0]);
		int addj = -1;
		for (size_t j = 0; j < 2; ++j)
		{
			glm::vec3 lNorm = float(addj) * dynamic_cast<OBB*>(b2->GetShape())->params[1] / 2.0f * (norms[1]);
			int addk = -1;
			for (size_t k = 0; k < 2; ++k)
			{
				glm::vec3 wNorm = float(addk) * dynamic_cast<OBB*>(b2->GetShape())->params[2] / 2.0f * (norms[2]);
				obbVerts.push_back(obbPos + hNorm + lNorm + wNorm);
				addk = 1;
			}
			addj = 1;
		}
		addi = 1;
	}

	float dist = glm::distance(b1->nextPosition, b2->nextPosition);

	if (true == moveB1 && true == moveB2)
	{
		// if the bodies haven't moved yet => no collision registration
		if (b1->nextPosition == b1->nextPosition || b2->nextPosition == b2->position)
		{
			return;
		}

		for (auto& p : obbVerts)
		{
			time = AnimatedSphereVSSphere(b1->position, b1->nextPosition, rad1, p, 0.0f);

			if (-1.0f != time)
			{
				Contact* contact = new Contact();
				contact->SetBodies(b1, b2);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_DYNAMIC);
				contacts.push_back(contact);
				return;
			}
		}

		glm::vec3 move = (b1->nextPosition - b1->position) - (b2->nextPosition - b2->position);
		time = 0.0f;

		for (; time < 1.0f; time += 0.1)
		{
			glm::vec3 posDiff = b1->position + time * move - b2->position;
			if (true == PointInOBB(posDiff, updParams, dynamic_cast<OBB*>(b2->GetShape())->GetNormals()))
			{
				Contact* contact = new Contact();
				contact->SetBodies(b1, b2);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_DYNAMIC);
				contacts.push_back(contact);
				return;
			}
		}
	}
	else if (true == moveB1)
	{
		// if the bodies haven't moved yet => no collision registration
		if (b1->nextPosition == b1->nextPosition)
		{
			return;
		}

		for (auto& p : obbVerts)
		{
			time = AnimatedSphereVSSphere(b1->position, b1->nextPosition, rad1, p, 0.0f);

			if (-1.0f != time)
			{
				Contact* contact = new Contact();
				contact->SetBodies(b1, b2);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_STATIC);
				contacts.push_back(contact);
				return;
			}
		}

		glm::vec3 move = b1->nextPosition - b1->position;
		time = 0.0f;

		for (; time < 1.0f; time += 0.1)
		{
			glm::vec3 posDiff = b1->position + time * move - b2->nextPosition;
			if (true == PointInOBB(posDiff, updParams, dynamic_cast<OBB*>(b2->GetShape())->GetNormals()))
			{
				Contact* contact = new Contact();
				contact->SetBodies(b1, b2);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_STATIC);
				contacts.push_back(contact);
				return;
			}
		}
	}
	else if (true == moveB2)
	{
		// if the bodies haven't moved yet => no collision registration
		if (b2->nextPosition == b2->position)
		{
			return;
		}

		glm::vec3 move = b2->nextPosition - b2->position;

		for (auto& p : obbVerts)
		{
			glm::vec3 prevPos;
			prevPos = b1->nextPosition + move;
			time = AnimatedSphereVSSphere(prevPos, b1->nextPosition, rad1, p, 0.0f);

			if (-1.0f != time)
			{
				Contact* contact = new Contact();
				contact->SetBodies(b2, b1);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_STATIC);
				contacts.push_back(contact);
				return;
			}
		}

		time = 0.0f;

		for (; time < 1.0f; time += 0.1)
		{
			glm::vec3 posDiff = b1->nextPosition + (1.0f - time) * move - b2->position;
			if (true == PointInOBB(posDiff, updParams, dynamic_cast<OBB*>(b2->GetShape())->GetNormals()))
			{
				Contact* contact = new Contact();
				contact->SetBodies(b2, b1);
				contact->SetTime(time);
				contact->SetType(ContactType::TYPE_DYNAMIC_V_STATIC);
				contacts.push_back(contact);
				return;
			}
		}
	}
}


/// Takes b1 and b2 bodies with OBB and Sphere shapes respectively
/// and std::vector of contacts that contains all the contacts at this frame
/// calls CollideSphereVSOBB since the function has already been implemented
void CollideOBBVSSphere(Body* b1, Body* b2, std::vector<Contact*>& contacts)
{
	CollideSphereVSOBB(b2, b1, contacts);
}




CollisionManager::CollisionManager()
{
	collisionFunctions[static_cast<int>(ShapeType::TYPE_SPHERE)][static_cast<int>(ShapeType::TYPE_SPHERE)] = CollideSphereVSphere;
	collisionFunctions[static_cast<int>(ShapeType::TYPE_OBB)][static_cast<int>(ShapeType::TYPE_OBB)] = CollideOBBVSOBB;

	collisionFunctions[static_cast<int>(ShapeType::TYPE_OBB)][static_cast<int>(ShapeType::TYPE_SPHERE)] = CollideOBBVSSphere;
	collisionFunctions[static_cast<int>(ShapeType::TYPE_SPHERE)][static_cast<int>(ShapeType::TYPE_OBB)] = CollideSphereVSOBB;
}



Contact::Contact() :
	cType(ContactType::TYPE_DEFAULT),
	time(0.0f),
	b1(nullptr), b2(nullptr)
{}

Contact::~Contact()
{
	b1 = nullptr;
	b2 = nullptr;
}

void Contact::SetBodies(Body* nb1, Body* nb2)
{
	b1 = nb1;
	b2 = nb2;
}


void CollisionManager::CheckCollision(Body* b1, Body* b2, std::vector<Contact*>& contacts)
{
	if (b1 == b2)
	{
		return;
	}

	collisionFunctions[static_cast<int>(b1->GetShape()->GetType())][static_cast<int>(b2->GetShape()->GetType())](b1, b2, contacts);
}


