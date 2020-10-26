#include "pch.h"
#include "ControlComponent.h"

#include "..//..//Managers//Managers.h"


ControlComponent::ControlComponent()
	:
	Component(COMPONENT_TYPE::TYPE_CONTROL)
{
    Initialize();
}

ControlComponent::~ControlComponent()
{
    End();
}


void ControlComponent::Initialize()
{
    inpStream = nullptr;
    controlee = nullptr;
}

void ControlComponent::End()
{
    inpStream = nullptr;
    controlee = nullptr;
}


void ControlComponent::Update(float dt)
{
    if (true == inpStream->KeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(controlee->baseWindow, true);
    }

    if (true == inpStream->KeyPressed(GLFW_KEY_W))
    {
        controlee->baseCamera->ProcessKeyboard(CAMERA_MOVEMENT::FORWARD, dt);
    }
    if (true == inpStream->KeyPressed(GLFW_KEY_S))
    {
        controlee->baseCamera->ProcessKeyboard(CAMERA_MOVEMENT::BACKWARD, dt);
    }
    if (true == inpStream->KeyPressed(GLFW_KEY_A))
    {
        controlee->baseCamera->ProcessKeyboard(CAMERA_MOVEMENT::LEFT, dt);
    }
    if (true == inpStream->KeyPressed(GLFW_KEY_D))
    {
        controlee->baseCamera->ProcessKeyboard(CAMERA_MOVEMENT::RIGHT, dt);
    }

    controlee->baseCamera->ProcessMouseMovement(inpStream->xMouse - inpStream->prevXMouse, inpStream->prevYMouse - inpStream->yMouse);
    controlee->baseCamera->ProcessMouseScroll(inpStream->scrollDifference);
}


void ControlComponent::PassControlee(GraphicsManager* nContr)
{
	controlee = nContr;
}

void ControlComponent::PassInputStream(InputManager* nInpStr)
{
	inpStream = nInpStr;
}
