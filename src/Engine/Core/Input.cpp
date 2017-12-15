#include <Engine\Core\Input.h>

namespace GameEngine {

	static int mouseX = 0;
	static int mouseY = 0;

	static bool keyStates[static_cast<unsigned int>(Keyboard::KEYBOARD_TOTAL)];
	static bool mouseButtons[static_cast<unsigned int>(Mouse::MOUSE_TOTAL)];
	static Controller controllers[static_cast<unsigned int>(Controllers::CONTROLLER_TOTAL)];


	/* Callback functions called from the Platform Layer */

	extern void CursorPositionCallback(int xpos, int ypos) {
		mouseX = xpos;
		mouseY = ypos;
	}

	extern void MouseButtonCallback(Mouse button, bool pressed)
	{
		mouseButtons[static_cast<unsigned int>(button)] = pressed;
	}


	extern void KeyCallback(unsigned int key, bool pressed)
	{
		keyStates[static_cast<unsigned int>(key)] = pressed;
	}

	void GamePadCallback(int ControllerIndex, Controller ControllerInfo)
	{
		controllers[ControllerIndex] = ControllerInfo;
	}


	/* Input class implementation */

	bool Input::IsKeyPressed(Keyboard key)
	{
		if (key >= Keyboard::KEYBOARD_TOTAL) {
			return false;
		}

		return keyStates[static_cast<unsigned int>(key)];
	}

	void Input::GetMousePosition(int &XPos, int &YPos)
	{
		XPos = mouseX;
		YPos = mouseY;
	}

	bool Input::IsMouseButtonPressed(Mouse Button)
	{
		if (Button >= Mouse::MOUSE_TOTAL)
		{
			return false;
		}

		return mouseButtons[static_cast<unsigned int>(Button)];
	}

	bool Input::IsControllerConnected(Controllers ControllerNumber)
	{
		if (ControllerNumber >= Controllers::CONTROLLER_TOTAL)
		{
			return false;
		}

		return controllers[static_cast<unsigned int>(ControllerNumber)].Conected;
	}

	bool Input::IsControllerButtonPressed(Controllers ControllerNumber, GamepadButtons ControllerButton)
	{
		if (!IsControllerConnected(ControllerNumber) || ControllerButton >= GamepadButtons::CONTROLLER_BUTTON_TOTAL)
			return false;

		return controllers[static_cast<unsigned int>(ControllerNumber)].Buttons[static_cast<unsigned int>(ControllerButton)] != 0;
	}

	float Input::GetControllerAxis(Controllers ControllerNumber, GamepadAxis ControllerAxis)
	{
		if (!IsControllerConnected(ControllerNumber)|| ControllerAxis >= GamepadAxis::CONTROLLER_AXIS_TOTAL)
			return 0.0f;

		return  controllers[static_cast<unsigned int>(ControllerNumber)].Axes[static_cast<unsigned int>(ControllerAxis)];
	}

}

