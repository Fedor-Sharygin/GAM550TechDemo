#include "pch.h"
#include "PhysicsManager.h"

#include "..//Objects//Components//Components.h"
#include "Managers.h"
#include "Events//Events.h"



PhysicsManager::PhysicsManager()
	:
	Manager(MANAGER_TYPE::TYPE_PHYSICS_MANAGER)
{
	Initialize();
}

PhysicsManager::~PhysicsManager()
{
	End();
}


void PhysicsManager::Initialize()
{
	mEventManager = nullptr;
	mFrManager = nullptr;
	mCollisionManager = new CollisionManager();
}

void PhysicsManager::End()
{
	mEventManager = nullptr;
	mFrManager = nullptr;
	delete mCollisionManager;
	for (auto& co : comps)
	{
		delete co;
	}
	comps.clear();
}


void PhysicsManager::Update(float dt)
{
	// Go through all registered body components
	// update all their positions
	// check collisions with mCollisionManager->CheckCollision(b1,b2,std::vector<Contact*>)

	for (auto& body : comps)
	{
		Body* curBody = dynamic_cast<Body*>(body);
		curBody->AddForce(curBody->GetMass() * gravity);

		curBody->Update(dt);
	}

	std::vector<Contact*> contacts;

	for (size_t i = 0; i < comps.size(); ++i)
	{
		auto& gob1 = comps[i];
		for (size_t j = i + 1; j < comps.size(); ++j)
		{
			auto& gob2 = comps[j];
			if (gob1 == gob2)
				continue;

			// if both objects are static => no collision check is needed
			if (false == static_cast<Body*>(gob1)->GetMove() && false == static_cast<Body*>(gob2)->GetMove())
				continue;

			mCollisionManager->CheckCollision(static_cast<Body*>(gob1), static_cast<Body*>(gob2), contacts);
		}
	}


	/// Redo the contact event registration
	for (auto& contact : contacts)
	{
		auto ncEv = mEventManager->PassEvent<ContactEvent>();
		ncEv->passedContact = contact;
		ncEv->timeLeft = contact->GetTime() * mFrManager->GetFrameTime();
	}

	// right now => just write that the collision happened between bodies of these types
	// in the future => create an event that bodies will handle
//	winrt::hstring names[static_cast<int>(ShapeType::TYPE_NUM)];
//	names[static_cast<int>(ShapeType::TYPE_SPHERE)] = L"sphere";
//	names[static_cast<int>(ShapeType::TYPE_OBB)] = L"obb";

//	winrt::hstring contactNames[static_cast<int>(ContactType::TYPE_DEFAULT)];
//	contactNames[static_cast<int>(ContactType::TYPE_DYNAMIC_V_DYNAMIC)] = L"DVD";
//	contactNames[static_cast<int>(ContactType::TYPE_DYNAMIC_V_STATIC)] = L"DVS";

//	int shapeNums[static_cast<int>(ShapeType::TYPE_NUM)];
//	shapeNums[static_cast<int>(ShapeType::TYPE_SPHERE)] = 0;
//	shapeNums[static_cast<int>(ShapeType::TYPE_OBB)] = 0;

	/// Go through all the registered contacts and create an event
//	for (auto& cont : contacts)
//	{
//		Event* contEvent = new Event(contactNames[static_cast<int>(cont->GetType())]);
//		contEvent->args = cont;
//		contEvent->timer = cont->GetTime() * float(mFrManager->FrameTime());
//		mEventManager->AddTimedEvent(contEvent);
//	}
//	mEventManager->Update(dt);
}



