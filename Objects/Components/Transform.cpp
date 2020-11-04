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


glm::vec3 Transform::GetUp()
{
	glm::vec3 front = GetForward();
	glm::vec3 right = GetRight();
	glm::vec3 up = glm::normalize(glm::cross(front, right));
	return up;
}

glm::vec3 Transform::GetForward()
{
	glm::vec3 front;
	float pitch = rotation.x;
	float yaw = rotation.y;
	float roll = rotation.z;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	return front;
}

glm::vec3 Transform::GetRight()
{
	glm::vec3 front = GetForward();
	glm::vec3 worldUp = GlobalUp();

	glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
	return right;
}




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



