#pragma once

#ifndef _FRAMERATE_H_
#define _FRAMERATE_H_

#include "Manager.h"


class FrameRateManager : public Manager
{
public:
	FrameRateManager();
	~FrameRateManager() = default;

	virtual void Update(float dt) override {};
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override {};
	virtual void End() override {};

	void SetFPS(int nFPS);

	float GetFrameTime() const;
public:
	/// How many frames have passed
	static unsigned int frameCount;
private:
private:
	/// Frames description
	float frameStart;
	float frameEnd;
	float frameTime;

	/// How many frames per second
	float fps;
	float frameTimeMin;
};


#endif

