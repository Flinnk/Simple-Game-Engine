#include <Engine\Core\Input.h>

namespace GameEngine {

	struct InputState
	{
		bool Previous = false;
		bool Current = false;
	};

	static int mouseX = 0;
	static int mouseY = 0;

	static InputState keyStates[static_cast<unsigned int>(Keyboard::KEYBOARD_TOTAL)];
	static InputState mouseButtons[static_cast<unsigned int>(Mouse::MOUSE_TOTAL)];
	static Controller controllers[static_cast<unsigned int>(Controllers::CONTROLLER_TOTAL)];


	/* Callback functions called from the Platform Layer */

	extern void CursorPositionCallback(int xpos, int ypos) {
		mouseX = xpos;
		mouseY = ypos;
	}

	extern void MouseButtonCallback(Mouse button, bool pressed)
	{
		mouseButtons[static_cast<unsigned int>(button)].Current = pressed;
	}


	extern void KeyCallback(unsigned int key, bool pressed)
	{
		keyStates[static_cast<unsigned int>(key)].Current = pressed;
	}

	void GamePadCallback(int ControllerIndex, Controller ControllerInfo)
	{
		controllers[ControllerIndex] = ControllerInfo;
	}


	extern void UpdateInputStates()
	{
		for (unsigned int i = 0; i < static_cast<unsigned int>(Keyboard::KEYBOARD_TOTAL); ++i) {
			keyStates[i].Previous = keyStates[i].Current;
		}

		for (unsigned int i = 0; i < static_cast<unsigned int>(Mouse::MOUSE_TOTAL); ++i) {
			mouseButtons[i].Previous = mouseButtons[i].Current;
		}
	}

	/* Input class implementation */

	bool Input::GetKey(Keyboard key)
	{
		if (key >= Keyboard::KEYBOARD_TOTAL) {
			return false;
		}

		return keyStates[static_cast<unsigned int>(key)].Current;
	}

	bool Input::GetKeyDown(Keyboard Key)
	{
		if (Key >= Keyboard::KEYBOARD_TOTAL) {
			return false;
		}


		InputState state = keyStates[static_cast<unsigned int>(Key)];
		return state.Current && (state.Current != state.Previous);
	}

	bool Input::GetKeyUp(Keyboard Key)
	{
		if (Key >= Keyboard::KEYBOARD_TOTAL) {
			return false;
		}


		InputState state = keyStates[static_cast<unsigned int>(Key)];
		return !state.Current && (state.Current != state.Previous);
	}



	void Input::GetMousePosition(int &XPos, int &YPos)
	{
		XPos = mouseX;
		YPos = mouseY;
	}

	bool Input::GetMouseButton(Mouse Button)
	{
		if (Button >= Mouse::MOUSE_TOTAL)
		{
			return false;
		}

		return mouseButtons[static_cast<unsigned int>(Button)].Current;
	}

	bool Input::GetMouseButtonDown(Mouse Button)
	{
		if (Button >= Mouse::MOUSE_TOTAL) {
			return false;
		}


		InputState state = mouseButtons[static_cast<unsigned int>(Button)];
		return state.Current && (state.Current != state.Previous);
	}

	bool Input::GetMouseButtonUp(Mouse Button)
	{
		if (Button >= Mouse::MOUSE_TOTAL) {
			return false;
		}


		InputState state = mouseButtons[static_cast<unsigned int>(Button)];
		return !state.Current && (state.Current != state.Previous);
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
		if (!IsControllerConnected(ControllerNumber) || ControllerAxis >= GamepadAxis::CONTROLLER_AXIS_TOTAL)
			return 0.0f;

		return  controllers[static_cast<unsigned int>(ControllerNumber)].Axes[static_cast<unsigned int>(ControllerAxis)];
	}

}

