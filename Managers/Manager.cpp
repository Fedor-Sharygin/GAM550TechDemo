#include "pch.h"
#include "Manager.h"

#include "..//Objects//Component.h"


/// Don't delete the provided components
/// game objects in charge of them will do it
Manager::~Manager()
{
	for (auto co : comps)
	{
		co = nullptr;
	}

	comps.clear();
}


void Manager::Update(float dt)
{
	for (auto& co : comps)
	{
		co->Update(dt);
	}
}

void Manager::FrameStart()
{
	for (auto& co : comps)
	{
		co->FrameStart();
	}
}

void Manager::FrameEnd()
{
	for (auto& co : comps)
	{
		co->FrameEnd();
	}
}



void Manager::SubscribeComponent(Component* nc)
{
	comps.push_back(nc);
}


