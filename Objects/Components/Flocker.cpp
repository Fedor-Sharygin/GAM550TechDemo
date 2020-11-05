#include "pch.h"
#include "Flocker.h"

#include "Flocking//Flock.h"

#include "Components.h"
#include "..//GameObject.h"
#include "..//..//Managers//FlockingManager.h"
#include "..//..//Managers//FrameRateManager.h"



Flocker::Flocker(float bodyRadius, float wanderAlpha, float sepRadius, float allRadius, float cohRadius, float evadeDistance, glm::vec3 speed, float acceleration)
	:
	Component(COMPONENT_TYPE::TYPE_AI),
	bRad(bodyRadius), wAl(wanderAlpha), sepRad(sepRadius),
	allRad(allRadius), cohRad(cohRadius), evDist(evadeDistance),
	mSpeed(speed), mAcceleration(acceleration),
	wander(nullptr), separation(nullptr), allignment(nullptr),
	cohesion(nullptr), evade(nullptr), sphereMover(nullptr)
{
	Initialize();
}

Flocker::~Flocker()
{
	End();
}


void Flocker::Update(float dt)
{
	if (0.0f == dt)
	{
		return;
	}
	glm::vec3 frontDifference = glm::vec3(0.0f)
		+ wander->GetForwVectAddition(dt) 
		+ separation->GetForwVectAddition(dt)
		+ allignment->GetForwVectAddition(dt) 
		+ cohesion->GetForwVectAddition(dt)
		+ evade->GetForwVectAddition(dt)
		;
//	frontDifference /= 200.0f;
//	frontDifference = glm::normalize(frontDifference);

	Transform* mTrans = this->GetOwner()->GetComponent<Transform>();
	glm::vec3 rotation = mTrans->GetRotation();
	glm::vec3 front = mTrans->GetForward();
	glm::vec3 pos = mTrans->GetPosition();
	
	glm::vec3 accelVec = mAcceleration * frontDifference;// (front + );// *10.0f;
	float speed = mSpeed.length();
	mTrans->SetPosition(pos + mSpeed * dt);
	mSpeed += accelVec * dt;

	//float cosVal = glm::dot(glm::normalize(mSpeed), front);
	///// since both vectors are unit vectors
	///// any overshooting with the cos value
	///// is only because of float inprecision
	//cosVal = cosVal > 1.0f ? 1.0f : (cosVal < -1.0f ? -1.0f : cosVal);
	//FrameRateManager::frameCount;
	//float yaw = glm::degrees(std::acosf(cosVal));
	//if (0.0f != yaw)
	//{
	//	glm::vec3 cr = glm::cross(front, mSpeed);
	//	float sign = cr.y > 0.0f ? -1.0f : 1.0f;
	//	yaw *= sign;
	//}
	mSpeed = speed * glm::normalize(mSpeed);

	rotation.y = glm::degrees(std::atan2f(mSpeed.x, mSpeed.z));
	mTrans->SetRotation(rotation);
}

void Flocker::FrameStart()
{}

void Flocker::FrameEnd()
{}


void Flocker::Initialize()
{
	wander = new Wander();
	wander->PassOwner(this);
	wander->SetHorRange(wAl);

	separation = new Separation();
	separation->PassOwner(this);
	separation->SetSquareRadius(sepRad * sepRad);

	allignment = new Allignment();
	allignment->PassOwner(this);
	allignment->SetSquareRadius(allRad * allRad);

	cohesion = new Cohesion();
	cohesion->PassOwner(this);
	cohesion->SetSquareRadius(cohRad * cohRad);

	evade = new Evade();
	evade->PassOwner(this);
	evade->SetEvadeSquareDistance(evDist * evDist);

	sphereMover = new SphereMover();
	sphereMover->PassOwner(this);
	sphereMover->SetSquareRadius(bRad * bRad);
}

void Flocker::End()
{}


void Flocker::HandleEvent(Event* nEvent)
{}


void Flocker::PassOwner(FlockingManager* nFlMan)
{
	flMan = nFlMan;
}

std::vector<Component*>& Flocker::GetAllFlockers()
{
	return flMan->GetFlockers();
}


