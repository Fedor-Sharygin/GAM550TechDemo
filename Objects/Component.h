#pragma once

#ifndef _COMP_H_
#define _COMP_H_



enum class COMPONENT_TYPE
{
	TYPE_TRANSFORM,
	TYPE_MODEL,
	TYPE_AUDIO,
	TYPE_SFX,
	TYPE_BODY,
	TYPE_AI,
	TYPE_CAMERA,
	TYPE_CONTROL,
	TYPE_AUDIO_LISTENER,
	TYPE_DEFAULT
};


class GameObject;
class Event;

class Component
{
public:
	Component(COMPONENT_TYPE nType = COMPONENT_TYPE::TYPE_DEFAULT) : cType(nType), owner(nullptr) {};
	virtual ~Component() {};

	virtual void Update(float dt) = 0;
	virtual void FrameStart() = 0;
	virtual void FrameEnd() = 0;

	virtual void Initialize() = 0;
	virtual void End() = 0;

	virtual void HandleEvent(Event* nEvent) = 0;

	void SetOwner(GameObject* nOwner);
	GameObject* GetOwner() const;
public:
	COMPONENT_TYPE cType;
private:
private:
protected:
protected:
	GameObject* owner;
};

#endif

