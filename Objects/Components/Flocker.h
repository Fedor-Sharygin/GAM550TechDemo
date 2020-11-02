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


class Flocker : public Component
{
public:
	Flocker();
	virtual ~Flocker();

	virtual void Update(float dt) override;
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override;
	virtual void End() override;

	virtual void HandleEvent(Event* nEvent) override;
public:
private:
private:
};


#endif

