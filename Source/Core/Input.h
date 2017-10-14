#ifndef INPUT_H
#define INPUT_H

namespace GameEngine {

	/* The unknown key */
#define KEY_UNKNOWN            -1

/* Printable keys */
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161 /* non-US #1 */
#define KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE         0x1B
#define KEY_ENTER              0x0D
#define KEY_TAB                0x09
#define KEY_BACKSPACE          0x08
#define KEY_INSERT             0x2D
#define KEY_DELETE             0x2E
#define KEY_RIGHT              0x27
#define KEY_LEFT               0x25
#define KEY_DOWN               0x28
#define KEY_UP                 0x26
#define KEY_HOME               0x24
#define KEY_END                0x23
#define KEY_CAPS_LOCK          0x14
#define KEY_SCROLL_LOCK        0x91
#define KEY_NUM_LOCK           0x90
#define KEY_PRINT_SCREEN       0x2C
#define KEY_PAUSE              0x13
#define KEY_F1             0x70
#define KEY_F2             0x71
#define KEY_F3             0x72
#define KEY_F4             0x73
#define KEY_F5             0x74
#define KEY_F6             0x75
#define KEY_F7             0x76
#define KEY_F8             0x77
#define KEY_F9             0x78
#define KEY_F10            0x79
#define KEY_F11            0x7A
#define KEY_F12            0x7B
#define KEY_F13            0x7C
#define KEY_F14            0x7D
#define KEY_F15            0x7E
#define KEY_F16            0x7F
#define KEY_F17            0x80
#define KEY_F18            0x81
#define KEY_F19            0x82
#define KEY_F20            0x83
#define KEY_F21            0x84
#define KEY_F22            0x85
#define KEY_F23            0x86
#define KEY_F24            0x87
#define KEY_NUMPAD0        0x60
#define KEY_NUMPAD1        0x61
#define KEY_NUMPAD2        0x62
#define KEY_NUMPAD3        0x63
#define KEY_NUMPAD4        0x64
#define KEY_NUMPAD5        0x65
#define KEY_NUMPAD6        0x66
#define KEY_NUMPAD7        0x67
#define KEY_NUMPAD8        0x68
#define KEY_NUMPAD9        0x69
#define KEY_MULTIPLY       0x6A
#define KEY_ADD            0x6B
#define KEY_SEPARATOR      0x6C
#define KEY_SUBTRACT       0x6D
#define KEY_DECIMAL        0x6E
#define KEY_DIVIDE         0x6F
#define KEY_SHIFT         0x10
#define KEY_CONTROL       0x11
#define KEY_ALT           0


#define MOUSE_BUTTON_LEFT  0
#define MOUSE_BUTTON_RIGHT   1
#define MOUSE_BUTTON_MIDDLE   2

#define CONTROLLER_1   0
#define CONTROLLER_2   1
#define CONTROLLER_3   2
#define CONTROLLER_4   3

#define CONTROLLER_BUTTON_A 0
#define CONTROLLER_BUTTON_B 1
#define CONTROLLER_BUTTON_X 2
#define CONTROLLER_BUTTON_Y 3
#define CONTROLLER_BUTTON_LB 4
#define CONTROLLER_BUTTON_RB 5
#define CONTROLLER_BUTTON_SELECT 6
#define CONTROLLER_BUTTON_START 7
#define CONTROLLER_BUTTON_LEFT_STICK 8
#define CONTROLLER_BUTTON_RIGHT_STICK 9
#define CONTROLLER_BUTTON_DPAD_UP 10
#define CONTROLLER_BUTTON_DPAD_RIGHT 11
#define CONTROLLER_BUTTON_DPAD_DOWN 12
#define CONTROLLER_BUTTON_DPAD_LEFT 13
#define CONTROLLER_BUTTON_LT 14
#define CONTROLLER_BUTTON_RT 15

#define CONTROLLER_AXIS_LEFT_STICK_HORIZONTAL 0
#define CONTROLLER_AXIS_LEFT_STICK_VERTICAL 1
#define CONTROLLER_AXIS_RIGHT_STICK_HORIZONTAL 2
#define CONTROLLER_AXIS_RIGHT_STICK_VERTICAL 3

	class Input {

	public:
		static void GetMousePosition(double &XPos, double &YPos);
		static bool IsKeyPressed(int Key);
		static bool IsMouseButtonPressed(int Button);
		static bool IsControllerConnected(int ControllerNumber);
		static bool IsControllerButtonPressed(int ControllerNumber, int ControllerButton);
		static float GetControllerAxis(int ControllerNumber, int ControllerAxis);
	};

}
#endif // !INPUT_H

