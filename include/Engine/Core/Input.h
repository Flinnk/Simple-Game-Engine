#ifndef INPUT_H
#define INPUT_H

namespace GameEngine {

	enum class Mouse : unsigned int {
		LEFT_BUTTON,
		RIGHT_BUTTON,
		MIDDLE_BUTTON,
		MOUSE_TOTAL
	};

	enum class Keyboard : unsigned int {
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,

		NUM0,
		NUM1,
		NUM2,
		NUM3,
		NUM4,
		NUM5,
		NUM6,
		NUM7,
		NUM8,
		NUM9,

		BACKSPACE,
		SPACE,
		LEFT_CONTROL,
		RIGHT_CONTROL,
		LEFT_SHIFT,
		RIGHT_SHIFT,
		LEFT_ALT,
		RIGHT_ALT,
		ENTER,
		TAB,
		ESCAPE,
		CAPSLOCK,

		UP_ARROW,
		DOWN_ARROW,
		LEFT_ARROW,
		RIGHT_ARROW,

		NUMPAD0,
		NUMPAD1,
		NUMPAD2,
		NUMPAD3,
		NUMPAD4,
		NUMPAD5,
		NUMPAD6,
		NUMPAD7,
		NUMPAD8,
		NUMPAD9,

		MULTIPLY,
		ADD,
		SEPARATOR,
		SUBTRACT,
		KDECIMAL,
		DIVIDE,
		NUMLOCK,

		COMMA,
		PERIOD,
		MINUS,

		KEYBOARD_TOTAL
	};

	/* Gamepad */

	enum class Controllers : unsigned int
	{
		CONTROLLER_1,
		CONTROLLER_2,
		CONTROLLER_3,
		CONTROLLER_4,
		CONTROLLER_TOTAL
	};

	enum class GamepadButtons : unsigned int
	{
		CONTROLLER_BUTTON_A,
		CONTROLLER_BUTTON_B,
		CONTROLLER_BUTTON_X,
		CONTROLLER_BUTTON_Y,
		CONTROLLER_BUTTON_LB,
		CONTROLLER_BUTTON_RB,
		CONTROLLER_BUTTON_SELECT,
		CONTROLLER_BUTTON_START,
		CONTROLLER_BUTTON_LEFT_STICK,
		CONTROLLER_BUTTON_RIGHT_STICK,
		CONTROLLER_BUTTON_DPAD_UP,
		CONTROLLER_BUTTON_DPAD_RIGHT,
		CONTROLLER_BUTTON_DPAD_DOWN,
		CONTROLLER_BUTTON_DPAD_LEFT,
		CONTROLLER_BUTTON_LT,
		CONTROLLER_BUTTON_RT,
		CONTROLLER_BUTTON_TOTAL
	}; 
	
	enum class GamepadAxis : unsigned int {
		CONTROLLER_AXIS_LEFT_STICK_HORIZONTAL,
		CONTROLLER_AXIS_LEFT_STICK_VERTICAL,
		CONTROLLER_AXIS_RIGHT_STICK_HORIZONTAL,
		CONTROLLER_AXIS_RIGHT_STICK_VERTICAL,
		CONTROLLER_AXIS_TOTAL
	};

#define CONTROLLER_DEADZONE_X 0.02f
#define CONTROLLER_DEADZONE_Y 0.02f

	/**
	* Structure to hold gamepad state
	*/
	struct Controller
	{
		bool Conected = false;
		bool Buttons[static_cast<unsigned int>(GamepadButtons::CONTROLLER_BUTTON_TOTAL)];
		float Axes[static_cast<unsigned int>(GamepadAxis::CONTROLLER_AXIS_TOTAL)];
	};

	/**
	* Class to retrieve input devices state. The input devices are keyboard, mouse and gamepads
	*/
	class Input {

	public:

		/**
		* Retrieves the 2D coordinates of the mouse position relative to the window frame
		* @param XPos Returns the X coordinate mouse position on the window
		* @param YPos Returns the Y coordinate mouse position on the window
		*/
		static void GetMousePosition(int &XPos, int &YPos);

		/**
		* Returns the state of a keyboard key
		* @param Key Key symbol to check
		* @return Whether the key is currently being pressed
		*/
		static bool IsKeyPressed(Keyboard Key);

		/**
		* Returns the state of a mouse button
		* @param Button Button to check
		* @return Whether the button is currently being pressed
		*/
		static bool IsMouseButtonPressed(Mouse Button);

		/**
		* Returns a gamepad conection state
		* @param ControllerNumber Controller index. Max=3
		* @return Whether the specified gamepad is currently connected
		*/
		static bool IsControllerConnected(Controllers ControllerNumber);

		/**
		* Returns the state of a specified gamepad button. In case the gamepad is not connected it will return false
		* @param ControllerNumber Controller index. Max=3
		* @param ControllerButton Button to check
		* @return Whether the button is currently being pressed
		*/
		static bool IsControllerButtonPressed(Controllers ControllerNumber, GamepadButtons ControllerButton);

		/**
		* Returns the state of a specified gamepad stick. In case the gamepad is not connected it will return 0.
		* @param ControllerNumber Controller index. Max=3
		* @param ControllerButton Axis to check
		* @return Returns the input for a stick axis. Values range from [0.0f,1.0f] with a deadzone value of 0.02f
		*/
		static float GetControllerAxis(Controllers ControllerNumber, GamepadAxis ControllerAxis);

	};

}
#endif // !INPUT_H

