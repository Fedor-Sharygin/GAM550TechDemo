#include "pch.h"
#include "Body.h"

#include "Components.h"

#include "..//..//Managers//Events//Events.h"
#include "..//..//Managers//CollisionManager.h"
#include "..//..//Managers//Managers.h"
#include "..//GameObject.h"

#include "Shapes.h"



void Body::Update(float dt)
{
	position = nextPosition;
	if (true == move)
	{
		nextPosition += velocity * dt;
		velocity += acceleration * dt;

		acceleration = sumOfForces / mass;

		if (nullptr != bodyShape)
		{
			if (ShapeType::TYPE_OBB == bodyShape->GetType())
			{
				dynamic_cast<OBB*>(bodyShape)->SetNormals(rotation);
			}
		}

		ResetForces();

		GetOwner()->GetComponent<Transform>()->SetPosition(position);
		GetOwner()->GetComponent<Transform>()->SetRotation(rotation);

		// Clear all previous frame collisions
		currentFrameCollisions.clear();

		// Check the processed collisions
		// if true => it has been checked on the previous frame. remember it
		// if false => the collision didn't appear in the last frame => delete it
		auto coll = processedCollisions.begin();
		while (processedCollisions.end() != coll)
		{
			if (true == coll->second)
			{
				coll->second = false;
				++coll;
			}
			else
			{
				processedCollisions.erase(coll++);
			}
		}
	}
}


void Body::HandleEvent(Event* event)
{
	if (true == move && true == react)
	{
		/// Work on collision reactions
		if (EVENT_TYPE::TYPE_CONTACT == event->evType)
		{
			Contact* cont = static_cast<ContactEvent*>(event)->passedContact;
			Body* b1 = cont->GetBody1();
			Body* b2 = cont->GetBody2();

			// if none of the 2 bodies are this body =>
			// there is no other body => no collision response
			Body* other = (this == b1) ? b2 : ((this == b2) ? b1 : nullptr);
			if (nullptr != other)
			{
				// Register the collision
				currentFrameCollisions.push_back(other);
				// Look through processed collisions
				// if not found => continue the process
				// otherwise => quit earlier
				if (processedCollisions.end() == processedCollisions.find(other))
				{
					processedCollisions[other] = true;
				}
				else
				{
					processedCollisions[other] = true;
					return;
				}
				// end of processed collision search


				// Process the collision
				ShapeType myType = this->GetShape()->GetType();
				ShapeType otherType = other->GetShape()->GetType();
				glm::vec3 toOtherCenNorm = other->position - this->position;
				if (ShapeType::TYPE_SPHERE == myType)
				{
					if (ShapeType::TYPE_SPHERE == otherType)
					{
						toOtherCenNorm = glm::normalize(toOtherCenNorm);
						
						velocity = 0.9f * (velocity - 
							2.0f * toOtherCenNorm * glm::dot(toOtherCenNorm, velocity));
					}
					if (ShapeType::TYPE_OBB == otherType)
					{
						OBB* otherOBB = dynamic_cast<OBB*>(other->GetShape());
						std::vector<glm::vec3>& norms = otherOBB->GetNormals();
						float localH = glm::dot(norms[0], toOtherCenNorm);
						float localL = glm::dot(norms[1], toOtherCenNorm);
						float localW = glm::dot(norms[2], toOtherCenNorm);

						float* params = otherOBB->params;

						glm::vec3 collisionNorm;

						float maxTopTanWid = params[2] / params[0];			///		   .+------+	
						float maxTopTanLen = params[1] / params[0];			///		 .' TOP  .'|	
																			///		+---+--+'  |	params[0] = H/height
						float maxSidTanHei = params[0] / params[2];			///		|   |  |SID|	params[1] = L/length
						float maxSidTanLen = params[1] / params[2];			///		|  .+--H---+	params[2] = W/width
																			///		|.FRO  | L'
						float maxFroTanWid = params[2] / params[0];			///		+---W--+'
						float maxFroTanHei = params[1] / params[0];			///


						float myWOverH = localW / localH;
						float myLOverH = localL / localH;

						float myHOverW = localH / localW;
						float myLOverW = localL / localW;

						float myWOverL = localW / localL;
						float myHOverL = localH / localL;

						if (maxTopTanWid >= myWOverH && maxTopTanLen >= myLOverH)
						{
							collisionNorm = norms[0];
						}

						if (maxSidTanHei >= myHOverW && maxSidTanLen >= myLOverW)
						{
							collisionNorm = norms[2];
						}

						if (maxFroTanHei >= myHOverL && maxFroTanWid >= myWOverL)
						{
							collisionNorm = norms[1];
						}

						velocity = 0.9f * (velocity -
							2.0f * collisionNorm * glm::dot(collisionNorm, velocity));
					}
				}

				if (ShapeType::TYPE_OBB == myType)
				{
					/// glm::vec3 Myypr = GetOwner()->GetComponent<Transform>()->GetRotation();
					/// Currently unused
					if (ShapeType::TYPE_SPHERE == otherType)
					{
						glm::normalize(toOtherCenNorm);

						velocity = 0.9f * (velocity -
							2.0f * toOtherCenNorm * glm::dot(toOtherCenNorm, velocity));
					}
					if (ShapeType::TYPE_OBB == otherType)
					{
						OBB* otherOBB = dynamic_cast<OBB*>(other->GetShape());
						std::vector<glm::vec3>& norms = otherOBB->GetNormals();
						float localH = glm::dot(norms[0], toOtherCenNorm);
						float localL = glm::dot(norms[1], toOtherCenNorm);
						float localW = glm::dot(norms[2], toOtherCenNorm);

						float* params = otherOBB->params;

						glm::vec3 collisionNorm;

						float maxTopTanWid = params[2] / params[0];			///		   .+------+	
						float maxTopTanLen = params[1] / params[0];			///		 .' TOP  .'|	
																			///		+---+--+'  |	params[0] = H/height
						float maxSidTanHei = params[0] / params[2];			///		|   |  |SID|	params[1] = L/length
						float maxSidTanLen = params[1] / params[2];			///		|  .+--H---+	params[2] = W/width
																			///		|.FRO  | L'
						float maxFroTanWid = params[2] / params[0];			///		+---W--+'
						float maxFroTanHei = params[1] / params[0];			///


						float myWOverH = localW / localH;
						float myLOverH = localL / localH;

						float myHOverW = localH / localW;
						float myLOverW = localL / localW;

						float myWOverL = localW / localL;
						float myHOverL = localH / localL;

						if (maxTopTanWid >= myWOverH && maxTopTanLen >= myLOverH)
						{
							collisionNorm = norms[0];
						}

						if (maxSidTanHei >= myHOverW && maxSidTanLen >= myLOverW)
						{
							collisionNorm = norms[2];
						}

						if (maxFroTanHei >= myHOverL && maxFroTanWid >= myWOverL)
						{
							collisionNorm = norms[1];
						}

						velocity = 0.9f * (velocity -
							2.0f * collisionNorm * glm::dot(collisionNorm, velocity));
					}
				}
			}
		}
	}
}


void Body::ResetForces()
{
	sumOfForces = glm::vec3(0.0f);
}

void Body::AddForce(glm::vec3 nForce)
{
	sumOfForces += nForce;
}


Shape* Body::SetBodyShape(ShapeType nBodyShape)
{
	// if there's a body shape => check its type
	// if same => return it
	// otherwise => redo
	if (nullptr != bodyShape && nBodyShape == bodyShape->GetType())
		return bodyShape;

	// we got out of the if statement and the body exists => wrong type
	if (nullptr != bodyShape)
		delete bodyShape;

	// depending on the type => create an according body type
	if (ShapeType::TYPE_SPHERE == nBodyShape)
		bodyShape = new Sphere();
	else if (ShapeType::TYPE_OBB == nBodyShape)
		bodyShape = new OBB();

	return bodyShape;
}
