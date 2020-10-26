#pragma once

#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "..//Component.h"


class GraphicsManager;
class InputManager;

class ControlComponent : public Component
{
public:
	ControlComponent();
	virtual ~ControlComponent();

	virtual void Update(float dt) override;
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override;
	virtual void End() override;

	void PassControlee(GraphicsManager* nContr);
	void PassInputStream(InputManager* nInpStr);
public:
private:
private:
	InputManager* inpStream;
	GraphicsManager* controlee;
};


#endif


