#include "pch.h"
#include "Transform.h"


Transform::Transform()
	:
	Component(COMPONENT_TYPE::TYPE_TRANSFORM)
{
	Initialize();
}

Transform::~Transform()
{
	End();
}


void Transform::Initialize()
{
	position = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	rotation = glm::vec3(0.0f);
}

void Transform::End()
{}




glm::vec3 Transform::GetPosition() const
{
	return position;
}

void Transform::SetPosition(glm::vec3 nPos)
{
	position = nPos;
}


glm::vec3 Transform::GetScale() const
{
	return scale;
}

void Transform::SetScale(glm::vec3 nScale)
{
	scale = nScale;
}


glm::vec3 Transform::GetRotation() const
{
	return rotation;
}

void Transform::SetRotation(glm::vec3 nRot)
{
	rotation = nRot;
}



