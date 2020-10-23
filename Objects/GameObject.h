#pragma once

#ifndef _GO_H_
#define _GO_H_


class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(float dt);
	void FrameStart();
	void FrameEnd();

	void Initialize();
	void End();
public:
private:
private:
	std::vector<Component*> goComponents;
};


#endif



