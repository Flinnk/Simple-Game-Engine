#include <Engine\Core\Input.h>
#include <Windows.h>
#include <XInput.h>
#include <cmath>

namespace GameEngine {
	/**
	* Function implemented on the Input class to receive input for each controller
	*/
	extern void GamePadCallback(int ControllerIndex,Controller ControllerInfo);
}

/**
* Retrives Gamepad Input when asked from Engine side calling the GamePadCallback function
*/
void UpdatePlatformInput()
{
	//Loop max controllers
	DWORD dwResult;
	for (DWORD i = 0; i< XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		GameEngine::Controller Controller;
		if (dwResult == ERROR_SUCCESS)
		{
			// Controller is connected 
			Controller.Conected = true;

			//Initialize Controller values
			for (int i = 0; i<16; ++i)
			{
				Controller.Buttons[i] = false;
			}
			for (int i = 0; i<4; ++i)
			{
				Controller.Axes[i] = 0.0f;
			}

			//Retrieve Button state
			Controller.Buttons[CONTROLLER_BUTTON_A] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_B] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_X] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_Y] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_LB] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_RB] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_LT] = state.Gamepad.bLeftTrigger > 0;
			Controller.Buttons[CONTROLLER_BUTTON_RT] = state.Gamepad.bRightTrigger > 0;
			Controller.Buttons[CONTROLLER_BUTTON_LEFT_STICK] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_RIGHT_STICK] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_SELECT] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_START] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_DPAD_UP] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_DPAD_RIGHT] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0; Controller.Buttons[CONTROLLER_BUTTON_LEFT_STICK] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_DPAD_DOWN] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0; Controller.Buttons[CONTROLLER_BUTTON_LEFT_STICK] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
			Controller.Buttons[CONTROLLER_BUTTON_DPAD_LEFT] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0; Controller.Buttons[CONTROLLER_BUTTON_LEFT_STICK] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
		
			//Retrieve axis input clamping its value to the range [-1,1] applying also a deadzone control
			float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
			float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);
			float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
			float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

			Controller.Axes[CONTROLLER_AXIS_LEFT_STICK_HORIZONTAL] = (std::abs(normLX) < CONTROLLER_DEADZONE_X) ? 0 : normLX;
			Controller.Axes[CONTROLLER_AXIS_RIGHT_STICK_HORIZONTAL] = (std::abs(normRX) < CONTROLLER_DEADZONE_X) ? 0 : normRX;;
			Controller.Axes[CONTROLLER_AXIS_LEFT_STICK_VERTICAL] = (abs(normLY) < CONTROLLER_DEADZONE_Y) ? 0 : normLY;
			Controller.Axes[CONTROLLER_AXIS_RIGHT_STICK_VERTICAL] = (abs(normRY) < CONTROLLER_DEADZONE_Y) ? 0 : normRY;

		}
		else
		{
			// Controller is not connected 
			Controller.Conected = false;

			//Initialize Controller values

			for (int i=0;i<16;++i)
			{
				Controller.Buttons[i] = false;
			}
			for (int i = 0; i<4; ++i)
			{
				Controller.Axes[i] = 0.0f;
			}
		}

		GameEngine::GamePadCallback(i, Controller);
	}
}