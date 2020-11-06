#pragma once

#include "Manager.h"

class Body;
class CollisionManager;
class GameObjectManager;
class EventManager;
class FrameRateManager;

const glm::vec3 gravity = glm::vec3(0.0f, -0.98f, 0.0f);

class PhysicsManager : public Manager
{
public:
	PhysicsManager();
	~PhysicsManager();

	virtual void Update(float dt) override;
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override;
	virtual void End() override;

	void PassFrameRateManager(FrameRateManager* nFrManager) { mFrManager = nFrManager; };
	void PassEventManager(EventManager* nEventManager) { mEventManager = nEventManager; };
public:
private:
private:
	CollisionManager* mCollisionManager;
	EventManager* mEventManager;
	FrameRateManager* mFrManager;
};

