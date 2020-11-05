#include "pch.h"

#include "Graphics//Shader.h"
#include "Graphics//Camera.h"

#include "Managers//Managers.h"

#include "GameManager.h"



int main()
{
    GameManager* fullGameManager = new GameManager();
    //fullGameManager->Demo(4);
    fullGameManager->Demo(26);

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


