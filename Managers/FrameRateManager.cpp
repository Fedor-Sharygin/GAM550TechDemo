#include "pch.h"
#include "FrameRateManager.h"


unsigned int FrameRateManager::frameCount = 0;


FrameRateManager::FrameRateManager()
	:
	Manager(MANAGER_TYPE::TYPE_FRAMERATE_MANAGER)
{
}


void FrameRateManager::SetFPS(int nFPS)
{
	fps = nFPS;
	frameTimeMin = (0.0f == fps) ? 0.0f : 1.0f / fps;
}



void FrameRateManager::FrameStart()
{
	frameStart = glfwGetTime();
}

void FrameRateManager::FrameEnd()
{
	frameEnd = glfwGetTime();

	while (frameEnd - frameStart < frameTimeMin)
	{
		frameEnd = glfwGetTime();
	}

	frameTime = frameEnd - frameStart;
	++frameCount;
}


float FrameRateManager::GetFrameTime() const
{
	return frameTime;
}

