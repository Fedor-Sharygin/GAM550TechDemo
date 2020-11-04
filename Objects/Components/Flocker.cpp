#include "pch.h"
#include "Flocker.h"

#include "Flocking//Flock.h"

#include "Components.h"
#include "..//GameObject.h"
#include "..//..//Managers//FlockingManager.h"



Flocker::Flocker(float bodyRadius, float wanderAlpha, float sepRadius, float allRadius, float cohRadius, float evadeDistance, float velocity)
	:
	Component(COMPONENT_TYPE::TYPE_AI),
	bRad(bodyRadius), wAl(wanderAlpha), sepRad(sepRadius),
	allRad(allRadius), cohRad(cohRadius), evDist(evadeDistance),
	mVelocity(velocity),
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
	glm::vec3 frontDifference =
		wander->GetForwVectAddition() + separation->GetForwVectAddition()
		+ allignment->GetForwVectAddition() + cohesion->GetForwVectAddition()
		+ evade->GetForwVectAddition();

	Transform* mTrans = this->GetOwner()->GetComponent<Transform>();
	glm::vec3 rotation = mTrans->GetRotation();
	glm::vec3 front = mTrans->GetForward();
	glm::vec3 pos = mTrans->GetPosition();
	glm::vec3 delta = front + frontDifference;

	delta = glm::normalize(delta);
	delta *= mVelocity * dt;

	mTrans->SetPosition(pos + delta);

	rotation.y = glm::degrees(std::atan2(delta.x, delta.z));
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


