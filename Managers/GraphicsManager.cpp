#include "pch.h"
#include "GraphicsManager.h"

#include "Managers.h"

#include "..//Graphics//Shader.h"
#include "..//Graphics//Camera.h"
#include "..//Graphics//Skybox.h"
#include "..//Objects//Components//ModelComponent.h"

#include "InputManager.h"



GraphicsManager::GraphicsManager(AssetManager* nLoader)
	:
	Manager(MANAGER_TYPE::TYPE_GRAPHICS_MANAGER),
	scrHeight(600.0f),
	scrWidth(800.0f),
	cubeVertices {
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	},
	time(0.0f),
	loader(nLoader)
{}


void GraphicsManager::Update(float dt)
{
	time += dt;

	baseShader->Use();
	baseShader->setVec3("light.position", lightPosition);
	baseShader->setVec3("viewPos", baseCamera->Position);
	
	glm::vec3 lightColor;
	lightColor.x = std::sinf(time * 2.0f);
	lightColor.y = std::sinf(time * 0.7f);
	lightColor.z = std::sinf(time * 1.3f);
	
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	
	baseShader->setVec3("light.ambient", ambientColor);
	baseShader->setVec3("light.diffuse", diffuseColor);
	baseShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	baseShader->SetFloat("material.shininess", 64.0f);

	glm::mat4 projection = glm::perspective(glm::radians(baseCamera->Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 200.0f);
	glm::mat4 view = baseCamera->GetViewMatrix();
	baseShader->setMat4("projection", projection);
	baseShader->setMat4("view", view);
/*	glm::mat4 model = glm::mat4(1.0f);
	baseShader->setMat4("model", model);
	// bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	// bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);*/

	for (auto& sculp : comps)
	{
		static_cast<ModelComponent*>(sculp)->Draw(baseShader);
	}

	lightCubeShader->Use();
	lightCubeShader->setMat4("projection", projection);
	lightCubeShader->setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	lightCubeShader->setMat4("model", model);

	glBindVertexArray(lightCubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

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

	baseShader = new Shader("Graphics/Shaders/mshader.vs", "Graphics/Shaders/mshader.fs");
	lightCubeShader = new Shader("Graphics/Shaders/lightCubeShader.vs", "Graphics/Shaders/lightCubeShader.fs");
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


/*	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/


	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	glGenVertexArrays(1, &lightCubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindVertexArray(lightCubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	lightPosition = glm::vec3(-2.0f, 4.0f, -1.0f);


/*	diffuseMap = loader->LoadTexture("container2.png");
	specularMap = loader->LoadTexture("container2_specular.png");

	baseShader->Use();
	baseShader->SetInt("material.diffuse", 0);
	baseShader->SetInt("material.specular", 1);*/
}


void GraphicsManager::End()
{
	comps.clear();

	glfwTerminate();
	delete baseWindow;
	delete baseShader;
	delete baseCamera;
}


