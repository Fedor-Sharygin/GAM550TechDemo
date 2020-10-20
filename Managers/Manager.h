#pragma once
#ifndef _MANAGER_H_
#define _MANAGER_H_


enum class MANAGER_TYPE
{
	TYPE_AUDIO_MANAGER,
	TYPE_PHYSICS_MANAGER,
	TYPE_GRAPHICS_MANAGER,
	TYPE_FRAMERATE_MANAGER,
	TYPE_INPUT_MANAGER,
	TYPE_ASSET_MANAGER,
	TYPE_DEFAULT
};


class Manager
{
public:
	Manager(MANAGER_TYPE nType) : mType(nType) {};
	virtual ~Manager() {};

	virtual void Update(float dt) = 0;
	virtual void FrameStart() = 0;
	virtual void FrameEnd() = 0;

	virtual void Initialize() = 0;
	virtual void End() = 0;
public:
	MANAGER_TYPE mType;
private:
private:
};


#endif

