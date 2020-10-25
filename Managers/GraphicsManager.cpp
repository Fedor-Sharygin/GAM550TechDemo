#include "pch.h"
#include "GraphicsManager.h"

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
	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(baseCamera->Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
	baseShader->setMat4("projection", projection);
	
	// mGrManager->baseCamera/view transformation
	glm::mat4 view = baseCamera->GetViewMatrix();
	baseShader->setMat4("view", view);

	for (auto& co : comps)
	{
		static_cast<ModelComponent*>(co)->Draw();
	}
}

void GraphicsManager::FrameStart()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	baseShader->Use();
}

void GraphicsManager::FrameEnd()
{
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
}


void GraphicsManager::End()
{
	glfwTerminate();
	delete baseWindow;
	delete baseShader;
	delete baseCamera;
}


