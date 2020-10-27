#include "pch.h"
#include "InputManager.h"


bool InputManager::mouseEntered = false, InputManager::mouseMoved = false, InputManager::mouseScrolled = false;
double InputManager::xMouse = 0.0, InputManager::yMouse = 0.0;
double InputManager::prevXMouse = 0.0, InputManager::prevYMouse = 0.0;
double InputManager::scrollDifference = 0.0;


InputManager::InputManager(GLFWwindow* nWnd)
	:
	Manager(MANAGER_TYPE::TYPE_INPUT_MANAGER),
	windowPtr(nWnd)
{}


void InputManager::Initialize()
{
	keyStates[GLFW_KEY_W] = false;
	keyStates[GLFW_KEY_A] = false;
	keyStates[GLFW_KEY_S] = false;
	keyStates[GLFW_KEY_D] = false;
	keyStates[GLFW_KEY_F1] = false;
	keyStates[GLFW_KEY_F2] = false;
	keyStates[GLFW_KEY_F3] = false;
	keyStates[GLFW_KEY_F4] = false;
	keyStates[GLFW_KEY_1] = false;
	keyStates[GLFW_KEY_2] = false;
	keyStates[GLFW_KEY_3] = false;
	keyStates[GLFW_KEY_4] = false;
	keyStates[GLFW_KEY_SPACE] = false;
	keyStates[GLFW_KEY_ENTER] = false;
	keyStates[GLFW_KEY_ESCAPE] = false;
	keyStates[GLFW_KEY_Q] = false;
	keyStates[GLFW_KEY_R] = false;
	prevKeyStates = keyStates;

	mouseStates[GLFW_MOUSE_BUTTON_LEFT] = false;
	mouseStates[GLFW_MOUSE_BUTTON_RIGHT] = false;
	mouseStates[GLFW_MOUSE_BUTTON_MIDDLE] = false;
	prevMouseStates = mouseStates;

	glfwGetCursorPos(windowPtr, &xMouse, &yMouse);
	prevXMouse = xMouse;
	prevYMouse = yMouse;
}


void InputManager::End()
{
	windowPtr = nullptr;
	comps.clear();
}


void InputManager::Update(float dt)
{
	prevKeyStates = keyStates;
	for (auto& [key, _] : keyStates)
	{
		keyStates[key] = GLFW_PRESS == glfwGetKey(windowPtr, key);
	}

	prevMouseStates = mouseStates;
	for (auto& [button, _] : mouseStates)
	{
		mouseStates[button] = glfwGetMouseButton(windowPtr, button);
	}

	/// Override mouse states if nothing is happening
	if (true == mouseMoved)
	{
		mouseMoved = false;
	}
	else if (false == mouseMoved)
	{
		prevXMouse = xMouse;
		prevYMouse = yMouse;
	}
	
	if (true == mouseScrolled)
	{
		mouseScrolled = false;
	}
	else if (false == mouseScrolled)
	{
		scrollDifference = 0.0f;
	}
}



bool InputManager::MouseButtonPressed(int mouseButton)
{
	return mouseStates[mouseButton];
}

bool InputManager::MouseButtonDown(int mouseButton)
{
	return false == prevMouseStates[mouseButton] && true == mouseStates[mouseButton];
}

bool InputManager::MouseButtonUp(int mouseButton)
{
	return true == prevMouseStates[mouseButton] && false == mouseStates[mouseButton];
}


bool InputManager::KeyPressed(int key)
{
	return keyStates[key];
}

bool InputManager::KeyDown(int key)
{
	return false == prevKeyStates[key] && true == keyStates[key];
}

bool InputManager::KeyUp(int key)
{
	return true == prevKeyStates[key] && false == keyStates[key];
}


