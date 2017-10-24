#include "Input.h"

namespace GameEngine {

#define MAX_KEYS 256
#define MAX_MOUSE_BUTTONS 7
#define MAX_CONTROLLERS 4
#define MAX_CONTROLLER_BUTTON 16
#define MAX_AXIS 4

	int mouseX = 0;
	int mouseY = 0;

	bool keyStates[MAX_KEYS];
	bool mouseButtons[MAX_MOUSE_BUTTONS];
	Controller controllers[MAX_CONTROLLERS];


	/* Callback functions called from the Platform Layer */

	extern void CursorPositionCallback(int xpos, int ypos) {
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

	void GamePadCallback(int ControllerIndex, Controller ControllerInfo)
	{
		controllers[ControllerIndex] = ControllerInfo;
	}


	/* Input class implementation */

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

		return controllers[ControllerNumber].Conected;
	}

	bool Input::IsControllerButtonPressed(int ControllerNumber, int ControllerButton)
	{
		if (!IsControllerConnected(ControllerNumber) || ControllerButton >= MAX_CONTROLLER_BUTTON)
			return false;

		return controllers[ControllerNumber].Buttons[ControllerButton] != 0;
	}

	float Input::GetControllerAxis(int ControllerNumber, int ControllerAxis)
	{
		if (!IsControllerConnected(ControllerNumber)|| ControllerAxis >= MAX_AXIS)
			return 0.0f;

		return  controllers[ControllerNumber].Axes[ControllerAxis];
	}

}

