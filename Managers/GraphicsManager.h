#pragma once

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "..//Graphics//Shader.h"
#include "..//Graphics//Camera.h"
#include "Manager.h"


class GraphicsManager : public Manager
{
public:
	GraphicsManager();
	~GraphicsManager() {};

	virtual void Update(float dt) override {};
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override {};

	static void FramebufferSizeFunc(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	};
public:
private:
private:
	GLFWwindow* baseWindow;
	Shader* baseShader;
	Camera* baseCamera;

	float scrWidth;
	float scrHeight;
};



#endif

