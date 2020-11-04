#include "pch.h"
#include "FlockingManager.h"

#include "..//Objects//Components//Flocker.h"



FlockingManager::FlockingManager()
	:
	Manager(MANAGER_TYPE::TYPE_FLOCKING_MANAGER)
{
	Initialize();
}

FlockingManager::~FlockingManager()
{
	End();
}

void FlockingManager::Update(float dt)
{
	for (auto& flo : comps)
	{
		flo->Update(dt);
	}
}

void FlockingManager::FrameStart()
{}

void FlockingManager::FrameEnd()
{}


void FlockingManager::Initialize()
{}

void FlockingManager::End()
{
	for (auto& flo : comps)
	{
		delete flo;
	}
	comps.clear();
}


std::vector<Component*>& FlockingManager::GetFlockers()
{
	return comps;
}


