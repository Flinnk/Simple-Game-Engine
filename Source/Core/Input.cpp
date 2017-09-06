#include "Input.h"
#include <GLFW\glfw3.h>

namespace GameEngine {

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 7
#define MAX_CONTROLLERS 3
#define MAX_CONTROLLER_BUTTON 16
#define MAX_AXIS 4

#define TRIGGER_BUTTON_AXIS_OFFSET 10 //In GLFW trigger buttons are in axis array //https://github.com/glfw/glfw/issues/700

	int mouseX = 0;
	int mouseY = 0;

	bool keyStates[MAX_KEYS];
	bool mouseButtons[MAX_MOUSE_BUTTONS];


	extern void CursorPositionCallback(double xpos, double ypos) {
		mouseX = xpos;
		mouseY = ypos;
	}

	extern void MouseButtonCallback(int button, bool pressed)
	{
		mouseButtons[button] = pressed;
	}


	extern void KeyCallback(int key, bool pressed)
	{
		keyStates[key] = pressed;
	}

	bool Input::IsKeyPressed(int key)
	{
		if (key > MAX_KEYS) {
			return false;
		}

		return keyStates[key];
	}

	void Input::GetMousePosition(int &XPos, int &YPos)
	{
		XPos = mouseX;
		YPos = mouseY;
	}

	bool Input::IsMouseButtonPressed(int Button)
	{
		if (Button > MAX_MOUSE_BUTTONS)
		{
			return false;
		}

		return mouseButtons[Button];
	}

	bool Input::IsControllerConnected(int ControllerNumber)
	{
		if (ControllerNumber > MAX_CONTROLLERS)
		{
			return false;
		}

		int present = glfwJoystickPresent(ControllerNumber);
		return present != 0;
	}

	bool Input::IsControllerButtonPressed(int ControllerNumber, int ControllerButton)
	{
		if (!IsControllerConnected(ControllerNumber))
			return false;

		int count;
		const unsigned char* buttons = glfwGetJoystickButtons(ControllerNumber, &count);

		int countAxis;
		const float* axes = glfwGetJoystickAxes(ControllerNumber, &countAxis);
		if (ControllerButton >= count && ControllerButton - TRIGGER_BUTTON_AXIS_OFFSET < countAxis)
		{
			return axes[ControllerButton - TRIGGER_BUTTON_AXIS_OFFSET] == 1;
		}
		else if (ControllerButton >= count)
		{
			return false;
		}

		return buttons[ControllerButton] != 0;
	}

	float Input::GetControllerAxis(int ControllerNumber, int ControllerAxis)
	{
		if (!IsControllerConnected(ControllerNumber))
			return 0.0f;

		int count;
		const float* axes = glfwGetJoystickAxes(ControllerNumber, &count);

		if (ControllerAxis >= MAX_AXIS)
			return 0.0f;

		return axes[ControllerAxis];
	}

}

