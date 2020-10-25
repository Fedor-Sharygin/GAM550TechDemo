#include "pch.h"
#include "GameObject.h"

#include "Component.h"



GameObject::GameObject()
	:
	goComponents(std::unordered_map<std::type_index, Component*>())
{}

GameObject::~GameObject()
{
	for (auto& [_, co] : goComponents)
	{
		delete co;
	}

	goComponents.clear();
}


void GameObject::Update(float dt)
{
	for (auto& [_, co] : goComponents)
	{
		if (COMPONENT_TYPE::TYPE_AUDIO != co->cType)
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


