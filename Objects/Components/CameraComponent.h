#pragma once

#ifndef _CAMERA_COMP_H_
#define _CAMERA_COMP_H_

#include "..//Component.h"


class Camera;

class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	virtual void Update(float dt) override;
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override;
	virtual void End() override;

	virtual void HandleEvent(Event* nEvent) override;
public:
private:
private:
	Camera* mCam;
};



#endif


