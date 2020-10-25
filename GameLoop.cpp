#include "pch.h"

#include "Graphics//Shader.h"
#include "Graphics//Camera.h"

#include "Managers//Managers.h"

#include "GameManager.h"



int main()
{
    GameManager* fullGameManager = new GameManager();

    /// Create 2 game objects for the demo
    for (size_t i = 0; i < 2; ++i)
    {
        fullGameManager->CreateGameObject();
    }
    fullGameManager->Demo(2);

    GLFWwindow* gameWindow = fullGameManager->GetGameWindow();
    while (0 == glfwWindowShouldClose(gameWindow))
    {
        fullGameManager->FrameStart();
        fullGameManager->Update();
        fullGameManager->FrameEnd();
    }

    delete fullGameManager;

	return 0;
}


/* Copy to the controller component if you write one
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
*/
