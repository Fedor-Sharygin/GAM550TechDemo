#pragma once

#ifndef _INPUT_H_
#define _INPUT_H_

#include "Manager.h"


class InputManager : public Manager
{
public:
	InputManager(GLFWwindow* nWnd);
	~InputManager() = default;

	virtual void Update(float dt) override;
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override {};

	static void MouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		if (false == mouseEntered)
		{
			prevXMouse = xpos;
			prevYMouse = ypos;
			mouseEntered = true;
		}

		float xoffset = xpos - prevXMouse;
		float yoffset = prevYMouse - ypos; // reversed since y-coordinates go from bottom to top

		prevXMouse = xpos;
		prevYMouse = ypos;
	};

	static void MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		scrollDifference = yoffset;
	};


	bool MouseButtonPressed(int mouseButton);
	bool MouseButtonDown(int mouseButton);
	bool MouseButtonUp(int mouseButton);

	bool KeyPressed(int key);
	bool KeyDown(int key);
	bool KeyUp(int key);
public:
	/// Static mouse parameters
	static bool mouseEntered;
	static double xMouse, yMouse;
	static double prevXMouse, prevYMouse;
	static double scrollDifference;
private:
private:
	GLFWwindow* windowPtr;

	/// States of the keys
	std::unordered_map<int, bool> keyStates;
	std::unordered_map<int, bool> prevKeyStates;

	/// State of the mouse
	std::unordered_map<int, bool> mouseStates;
	std::unordered_map<int, bool> prevMouseStates;

	/// Gamepad input/state
};


#endif

