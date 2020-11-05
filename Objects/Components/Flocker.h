#pragma once

#ifndef _FLOCKER_H_
#define _FLOCKER_H_

#include "..//Component.h"


class Wander;
class Separation;
class Allignment;
class Cohesion;
class Evade;

/// Uniform shape for an easier
/// time implementing evasion
class SphereMover;

/// We need the access to other
/// Flocker components to see their
/// positions and allign, cohide(?), separate, evade
class FlockingManager;

class Flocker : public Component
{
public:
	Flocker(float bodyRadius, float wanderAlpha, float sepRadius, float allRadius, float cohRadius, float evadeDistance, glm::vec3 speed, float acceleration);
	virtual ~Flocker();

	virtual void Update(float dt) override;
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override;
	virtual void End() override;

	virtual void HandleEvent(Event* nEvent) override;

	void PassOwner(FlockingManager* nFlMan);
	std::vector<Component*>& GetAllFlockers();

	SphereMover* GetBody() { return sphereMover; };
public:
private:
private:
	FlockingManager* flMan;
	
	float bRad, wAl, sepRad, allRad, cohRad, evDist;
	float mAcceleration;

	glm::vec3 mSpeed;

	Wander* wander;
	Separation* separation;
	Allignment* allignment;
	Cohesion* cohesion;
	Evade* evade;
	SphereMover* sphereMover;
};


#endif

