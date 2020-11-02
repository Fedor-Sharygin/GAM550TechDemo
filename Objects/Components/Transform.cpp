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

glm::mat4 Transform::GetRotationMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	return model;
}

glm::vec3 Transform::GetUp()
{
	glm::mat4 rot = GetRotationMatrix();
	
}

glm::vec3 Transform::GetForward()
{}

glm::vec3 Transform::GetRight()
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



