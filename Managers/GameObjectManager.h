#pragma once

#ifndef _GO_MANAGER_H_
#define _GO_MANAGER_H_

#include "Manager.h"


class GameObject;

class GameObjectManager : public Manager
{
public:
	GameObjectManager();
	~GameObjectManager() = default;

	virtual void Update(float dt) override;
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override;
	virtual void End() override;
public:
private:
private:
	std::vector<GameObject*> gameObjects;
};



#endif


