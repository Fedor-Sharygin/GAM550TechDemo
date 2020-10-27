#pragma once

#include "Manager.h"

class Body;
class CollisionManager;
class GameObjectManager;
class EventManager;
class FrameRateManager;

const glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f);

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

	void SetGOManager(GameObjectManager* nGOManager);
	void SetFrManager(FrameRateManager* nFrManager);
	void SetEventManager(EventManager* nEventManager);
public:
private:
private:
	CollisionManager* mCollisionManager;
	GameObjectManager* mGOManager;
	EventManager* mEventManager;
	FrameRateManager* mFrManager;
};

