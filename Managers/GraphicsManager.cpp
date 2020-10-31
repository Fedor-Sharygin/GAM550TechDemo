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
	baseShader->Use();
	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(baseCamera->Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
	baseShader->SetMat4("projection", projection);
	
	// mGrManager->baseCamera/view transformation
	glm::mat4 view = baseCamera->GetViewMatrix();
	baseShader->SetMat4("view", view);

	/// used for reflections: not this demo
	//baseShader->setVec3("cameraPos", baseCamera->Position);

	for (auto& co : comps)
	{
		static_cast<ModelComponent*>(co)->Draw();
	}

	/// Change the depth test to draw
	/// the skybox as if it was far away
	glDepthFunc(GL_LEQUAL);
	sbShader->Use();
	/// get rid of camera's translation
	view = glm::mat4(glm::mat3(view));
	sbShader->SetMat4("projection", projection);
	sbShader->SetMat4("view", view);
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

	baseShader = new Shader("Graphics/Shaders/triangleShader.vert", "Graphics/Shaders/triangleShader.frag");
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

	prtShader = new Shader("Graphics/Shaders/particleShader.vs", "Graphics/Shaders/particleShader.fs");
}


void GraphicsManager::End()
{
	comps.clear();

	glfwTerminate();
	delete baseWindow;
	delete baseShader;
	delete baseCamera;
}


