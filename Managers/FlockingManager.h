#pragma once

#ifndef _FLOCK_MANAGER_H_
#define _FLOCK_MANAGER_H_

#include "Manager.h"


class Component;

class FlockingManager : public Manager
{
public:
	FlockingManager();
	~FlockingManager();

	virtual void Update(float dt) override;
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override;
	virtual void End() override;

	std::vector<Component*>& GetFlockers();
public:
private:
private:
};


#endif

