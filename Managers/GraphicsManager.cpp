#include "pch.h"
#include "GraphicsManager.h"

#include "..//Graphics//Shader.h"
#include "..//Graphics//Camera.h"
#include "..//Graphics//Skybox.h"
#include "..//Objects//Components//ModelComponent.h"

#include "InputManager.h"



GraphicsManager::GraphicsManager()
	:
	Manager(MANAGER_TYPE::TYPE_GRAPHICS_MANAGER),
	scrHeight(600.0f),
	scrWidth(800.0f)
{}


void GraphicsManager::Update(float dt)
{
	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 1.0f, far_plane = 200.0f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	shadowShader->Use();
	shadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		for (auto& co : comps)
		{
			static_cast<ModelComponent*>(co)->Draw(shadowShader);
		}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// reset viewport
	glViewport(0, 0, scrWidth, scrHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	baseShader->Use();
	glm::mat4 projection = glm::perspective(glm::radians(baseCamera->Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
	glm::mat4 view = baseCamera->GetViewMatrix();
	baseShader->setMat4("projection", projection);
	baseShader->setMat4("view", view);
	// set light uniforms
	baseShader->setVec3("viewPos", baseCamera->Position);
	baseShader->setVec3("lightPos", lightPosition);
	baseShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

	for (auto& co : comps)
	{
		static_cast<ModelComponent*>(co)->Draw(baseShader);
	}

	/// Change the depth test to draw
	/// the skybox as if it was far away
	glDepthFunc(GL_LEQUAL);
	sbShader->Use();
	/// get rid of camera's translation
	view = glm::mat4(glm::mat3(view));
	sbShader->setMat4("projection", projection);
	sbShader->setMat4("view", view);
	skybox->Draw();
	glDepthFunc(GL_LESS);
}

void GraphicsManager::FrameStart()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	baseShader->Use();
/// Used for reflections => not now
//	baseShader->SetInt("skybox", 0);
	sbShader->Use();
	sbShader->SetInt("skybox", 0);
}

void GraphicsManager::FrameEnd()
{
	sbShader->Unuse();
	baseShader->Unuse();
	glfwSwapBuffers(baseWindow);
}


void GraphicsManager::Initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	baseWindow = glfwCreateWindow(scrWidth, scrHeight, "GAM550Demo", nullptr, nullptr);
	if (nullptr == baseWindow)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(baseWindow);
	glfwSetFramebufferSizeCallback(baseWindow, GraphicsManager::FramebufferSizeFunc);
	glfwSetCursorPosCallback(baseWindow, InputManager::MouseMove);
	glfwSetScrollCallback(baseWindow, InputManager::MouseScroll);

	// tell GLFW to capture our mouse
	glfwSetInputMode(baseWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (0 == gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	baseShader = new Shader("Graphics/Shaders/shadowMapShader.vs", "Graphics/Shaders/shadowMapShader.fs");
	baseCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	std::vector<std::string> faces
	{
		"skybox/right.jpg",
		"skybox/left.jpg",
		"skybox/top.jpg",
		"skybox/bottom.jpg",
		"skybox/front.jpg",
		"skybox/back.jpg"
	};
	skybox = new Skybox(faces);
	skybox->PassDrawer(this);
	sbShader = new Shader("Graphics/Shaders/skyboxShader.vs", "Graphics/Shaders/skyboxShader.fs");

	shadowShader = new Shader("Graphics/Shaders/shadowDepthShader.vs", "Graphics/Shaders/shadowDepthShader.fs");
	shadowMapHeight = shadowMapWidth = 1024;
	lightPosition = glm::vec3(0.0f, 10.0f, 10.0f);
	glGenFramebuffers(1, &shadowFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	baseShader->Use();
	baseShader->SetInt("diffuseTexture", 0);
	baseShader->SetInt("shadowMap", 1);

	//shadowShader->Use();
	//shadowShader->SetInt("depthMap", 0);
}


void GraphicsManager::End()
{
	comps.clear();

	glfwTerminate();
	delete baseWindow;
	delete baseShader;
	delete baseCamera;
}


