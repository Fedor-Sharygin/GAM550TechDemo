#pragma once

#ifndef _COMP_H_
#define _COMP_H_

class GameObject;

class Component
{
public:
	Component();
	~Component();

	void Update(float dt);
	void FrameStart();
	void FrameEnd();

	void Initialize();
	void End();
public:
private:
private:
};

#endif

