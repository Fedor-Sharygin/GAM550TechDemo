#pragma once

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Manager.h"

class Shader;
class Camera;
class Skybox;

class AssetManager;

class GraphicsManager : public Manager
{
public:
	GraphicsManager(AssetManager* nLoader);
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

	Shader* lightCubeShader;
	float cubeVertices[8 * 6 * 6];
	unsigned int VBO, cubeVAO;
	unsigned int lightCubeVAO;
	unsigned int diffuseMap;
	unsigned int specularMap;
	float time;

	glm::vec3 lightPosition;

	/// shader that is used to render the skybox
	Shader* sbShader;
	Skybox* skybox;

	/// shadow mapping shader
//	Shader* shadowShader;
//	unsigned int shadowFBO, depthMap;
//	unsigned int shadowMapWidth, shadowMapHeight;
private:
private:
	float scrWidth;
	float scrHeight;

	AssetManager* loader;
};



#endif

