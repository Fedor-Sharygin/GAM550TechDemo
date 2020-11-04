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
	TYPE_EVENT_MANAGER,
	TYPE_FLOCKING_MANAGER,
	TYPE_DEFAULT
};


class Component;

class Manager
{
public:
	Manager(MANAGER_TYPE nType) : mType(nType), comps(std::vector<Component*>()) {};
	virtual ~Manager();

	virtual void Update(float dt);	/// Update all of the components associated with this manager
	virtual void FrameStart();		/// FrameStart all of the components associated with this manager
	virtual void FrameEnd();		/// FrameEnd all of the components associated with this manager

	virtual void Initialize() = 0;
	virtual void End() = 0;

	void SubscribeComponent(Component* nc);
public:
	MANAGER_TYPE mType;
private:
private:
protected:
	/// saves all of the created components
	/// that this manager works with
	std::vector<Component*> comps;
protected:
};


#endif

