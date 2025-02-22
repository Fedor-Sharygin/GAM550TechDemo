#include "pch.h"
#include "GraphicsManager.h"

#include "Managers.h"

#include "..//Graphics//Shader.h"
#include "..//Graphics//Camera.h"
#include "..//Graphics//Skybox.h"
#include "..//Objects//Components//ModelComponent.h"
#include "..//Objects//Components//ParticleEmitter.h"

#include "InputManager.h"



GraphicsManager::GraphicsManager(AssetManager* nLoader)
	:
	Manager(MANAGER_TYPE::TYPE_GRAPHICS_MANAGER),
	scrHeight(600.0f),
	scrWidth(800.0f),
	cubeVertices{
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	},
	colorTime(0.0f),
	lightPosition(glm::vec3(0.0f, 20.0f, 10.0f))
{}


void GraphicsManager::Update(float dt)
{
	colorTime += dt;

	baseShader->Use();
	baseShader->SetVec3("light.position", lightPosition);
	baseShader->SetVec3("viewPos", baseCamera->Position);

	// light properties
	glm::vec3 lightColor;
	lightColor.x = sin(colorTime * 2.0f);
	lightColor.y = sin(colorTime * 0.7f);
	lightColor.z = sin(colorTime * 1.3f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(2.2f); // high influence
	baseShader->SetVec3("light.ambient", ambientColor);
	baseShader->SetVec3("light.diffuse", diffuseColor);
	baseShader->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// material properties
	baseShader->SetFloat("material.shininess", 8.0f);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(baseCamera->Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
	glm::mat4 view = baseCamera->GetViewMatrix();
	baseShader->setMat4("projection", projection);
	baseShader->setMat4("view", view);

	for (auto& sculp : comps)
	{
		if (COMPONENT_TYPE::TYPE_PARTICLE_EMITTER != sculp->cType)
		{
			static_cast<ModelComponent*>(sculp)->Draw(baseShader);
		}
	}

	/// Draw the light cube
	lcShader->Use();
	lcShader->setMat4("projection", projection);
	lcShader->setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	lcShader->setMat4("model", model);

	glBindVertexArray(lcVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	/// Draw particles
	particleShader->Use();
	particleShader->setMat4("projection", projection);
	particleShader->setMat4("view", view);
	for (auto& part : comps)
	{
		if (COMPONENT_TYPE::TYPE_PARTICLE_EMITTER == part->cType)
		{
			static_cast<ParticleEmitter*>(part)->Draw(particleShader);
			part->Update(dt);
		}
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
	sbShader->Use();
	sbShader->SetInt("skybox", 0);
}

void GraphicsManager::FrameEnd()
{
	baseShader->Unuse();

	glfwSwapBuffers(baseWindow);
	glfwPollEvents();
}


void GraphicsManager::Initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	glEnable(GL_BLEND);

	baseShader = new Shader("Graphics/Shaders/mshader.vs", "Graphics/Shaders/mshader.fs");
	baseCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	std::vector<std::string> faces
	{
		"discoSkybox/discoRight.jpg",
		"discoSkybox/discoLeft.jpg",
		"discoSkybox/discoTop.jpg",
		"discoSkybox/discoBottom.jpg",
		"discoSkybox/discoFront.jpg",
		"discoSkybox/discoBack.jpg"
	};
	skybox = new Skybox(faces);
	skybox->PassDrawer(this);
	sbShader = new Shader("Graphics/Shaders/skyboxShader.vs", "Graphics/Shaders/skyboxShader.fs");


	lcShader = new Shader("Graphics/Shaders/lightCube.vs", "Graphics/Shaders/lightCube.fs");
	
	glGenVertexArrays(1, &lcVAO);
	glGenBuffers(1, &lcVBO);

	glBindBuffer(GL_ARRAY_BUFFER, lcVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindVertexArray(lcVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	particleShader = new Shader("Graphics/Shaders/particleShader.vs", "Graphics/Shaders/particleShader.fs");
}


void GraphicsManager::End()
{
	comps.clear();

	glfwTerminate();
	delete baseWindow;
	delete baseShader;
	delete baseCamera;
}


