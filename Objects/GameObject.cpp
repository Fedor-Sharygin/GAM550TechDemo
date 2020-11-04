#include "pch.h"
#include "GameObject.h"

#include "Component.h"



GameObject::GameObject()
	:
	goComponents(std::unordered_map<std::type_index, Component*>()),
	generator()
{}

GameObject::~GameObject()
{
	for (auto& [_, co] : goComponents)
	{
		delete co;
	}

	goComponents.clear();
}


void GameObject::Update(float dt, std::vector<COMPONENT_TYPE> nonEssential)
{
	for (auto& [_, co] : goComponents)
	{
		if (nonEssential.end() == std::find(nonEssential.begin(), nonEssential.end(), co->cType))
		{
			co->Update(dt);
		}
	}
}

void GameObject::FrameStart()
{
	for (auto& [_, co] : goComponents)
	{
		co->FrameStart();
	}
}

void GameObject::FrameEnd()
{
	for (auto& [_, co] : goComponents)
	{
		co->FrameEnd();
	}
}


