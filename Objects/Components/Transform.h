#pragma once

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "..//Component.h"


class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	virtual void Update(float dt) override {};
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override;
	virtual void End() override;

	virtual void HandleEvent(Event* nEvent) override {};


	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 nPos);

	glm::vec3 GetScale() const;
	void SetScale(glm::vec3 nScale);

	glm::vec3 GetRotation() const;
	void SetRotation(glm::vec3 nRot);

	static glm::vec3 GlobalUp()			{ return glm::vec3(0.0f, 1.0f, 0.0f); };
	static glm::vec3 GlobalRight()		{ return glm::vec3(-1.0f, 0.0f, 0.0f); };
	static glm::vec3 GlobalForward()	{ return glm::vec3(0.0f, 0.0f, -1.0f); };
public:
private:
private:
	glm::vec3 position;		/// the position of this object
	glm::vec3 scale;		/// the scale of this object
	glm::vec3 rotation;		/// the rotation of this object in quaternions
};




#endif

