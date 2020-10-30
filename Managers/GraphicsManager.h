#pragma once

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Manager.h"

class Shader;
class Camera;
class Skybox;

class GraphicsManager : public Manager
{
public:
	GraphicsManager();
	~GraphicsManager() = default;

	virtual void Update(float dt) override;
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override;
	virtual void End() override;

	static void FramebufferSizeFunc(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	};
public:
	GLFWwindow* baseWindow;
	Shader* baseShader;
	Camera* baseCamera;

	/// shader that is used to render the skybox
	Shader* sbShader;
	Skybox* skybox;
private:
private:
	float scrWidth;
	float scrHeight;
};



#endif

