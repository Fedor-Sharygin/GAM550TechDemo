#include "pch.h"

#include "Graphics//Shader.h"
#include "Graphics//Camera.h"

#include "Managers//Manager.h"
#include "Managers//GraphicsManager.h"
#include "Managers//FrameRateManager.h"
#include "Managers//InputManager.h"
#include "Managers//AssetManager.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GraphicsManager* grManager, InputManager* inManager);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// mGrManager->baseCamera
// mGrManager->baseCamera* mGrManager->baseCamera = new mGrManager->baseCamera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{
    GraphicsManager* mGrManager = new GraphicsManager();
    mGrManager->Initialize();

    AssetManager* mAssetManager = new AssetManager();
    mAssetManager->Initialize();

    InputManager* mInputManager = new InputManager(mGrManager->baseWindow);
    mInputManager->Initialize();

    FrameRateManager* mFrRManager = new FrameRateManager();
    mFrRManager->Initialize();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int& texture1 = mAssetManager->LoadTexture("wall.jpg");
    unsigned int& texture2 = mAssetManager->LoadTexture("awesomeface.png");

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    mGrManager->baseShader->Use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(mGrManager->baseShader->ID, "texture1"), 0);
    // or set it via the texture class
    mGrManager->baseShader->SetInt("texture2", 1);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // render loop
    // -----------
	while (0 == glfwWindowShouldClose(mGrManager->baseWindow))
	{
        mFrRManager->FrameStart();

        deltaTime = mFrRManager->GetFrameTime();

        mInputManager->Update(deltaTime);

		// input
		processInput(mGrManager, mInputManager);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

		mGrManager->baseShader->Use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(mGrManager->baseCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        mGrManager->baseShader->setMat4("projection", projection);

        // mGrManager->baseCamera/view transformation
        glm::mat4 view = mGrManager->baseCamera->GetViewMatrix();
        mGrManager->baseShader->setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = glfwGetTime() * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            mGrManager->baseShader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

		// check and call events
		// swap buffers
		glfwSwapBuffers(mGrManager->baseWindow);
		glfwPollEvents();

        mFrRManager->FrameEnd();
	}

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);


//	glfwTerminate();

    delete mGrManager;
    delete mFrRManager;
    delete mInputManager;
    delete mAssetManager;

	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GraphicsManager* grManager, InputManager* inManager)
{
    if (true == inManager->KeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(grManager->baseWindow, true);
    }

    if (true == inManager->KeyPressed(GLFW_KEY_W))
    {
        grManager->baseCamera->ProcessKeyboard(CAMERA_MOVEMENT::FORWARD, deltaTime);
    }
    if (true == inManager->KeyPressed(GLFW_KEY_S))
    {
        grManager->baseCamera->ProcessKeyboard(CAMERA_MOVEMENT::BACKWARD, deltaTime);
    }
    if (true == inManager->KeyPressed(GLFW_KEY_A))
    {
        grManager->baseCamera->ProcessKeyboard(CAMERA_MOVEMENT::LEFT, deltaTime);
    }
    if (true == inManager->KeyPressed(GLFW_KEY_D))
    {
        grManager->baseCamera->ProcessKeyboard(CAMERA_MOVEMENT::RIGHT, deltaTime);
    }

    grManager->baseCamera->ProcessMouseMovement(inManager->xMouse - inManager->prevXMouse, inManager->prevYMouse - inManager->yMouse);
    grManager->baseCamera->ProcessMouseScroll(inManager->scrollDifference);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

//    mGrManager->baseCamera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
//    mGrManager->baseCamera->ProcessMouseScroll(yoffset);
}

