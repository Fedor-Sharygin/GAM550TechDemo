#include "pch.h"
#include "Component.h"

#include "GameObject.h"



void Component::SetOwner(GameObject* nOwner)
{
	owner = nOwner;
}

GameObject* Component::GetOwner() const
{
	return owner;
}


