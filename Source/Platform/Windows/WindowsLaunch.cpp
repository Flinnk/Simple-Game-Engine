#include <Windows.h>
#include "..\..\Core\Engine.h"
#include "..\..\Renderer\IGraphicContext.h"
#include "WindowsGraphicContext.h"

namespace GameEngine {

	IGraphicContext* CreateGraphicContext()
	{
		return new WindowsGraphicContext();
	}
}

bool IsUniqueInstance(LPCSTR WindowClassName)
{
	HWND Window = FindWindow(WindowClassName, NULL);
	if (Window)
	{
		ShowWindow(Window, SW_SHOWNORMAL);
		SetFocus(Window);
		SetForegroundWindow(Window);
		SetActiveWindow(Window);
	}

	return !Window;
}

static bool Running = true;

LRESULT CALLBACK WinMessageCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{

	LRESULT Result = 0;

	switch (Message)
	{
	case WM_SIZE:
	{
		OutputDebugStringA("WM_SIZE\n");
		break;
	}
	case WM_DESTROY:
	{
		Running = false;
		OutputDebugStringA("WM_DESTROY\n");
		break;
	}
	case WM_CLOSE:
	{
		Running = false;
		OutputDebugStringA("WM_CLOSE\n");
		break;
	}
	case WM_ACTIVATEAPP:
	{
		OutputDebugStringA("WM_ACTIVATEAPP\n");
		break;
	}
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		unsigned int VKCode = WParam;
		/*bool WasDown = ((LParam & (1 << 30)) != 0);
		bool IsDown = ((LParam & (1 << 31)) == 0);

		if (VKCode == 'W')
		{
			if (IsDown)
				OutputDebugStringA("W\n");
		}*/

		if (VKCode == VK_F4 && (LParam & (1 << 29)))//Lcon 1<<29 comprobamos si se ha presionado ALT o no
		{
			Running = false;
		}

		break;
	}

	default:
		Result = DefWindowProc(Window, Message, WParam, LParam);
		break;
	}

	return Result;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS WindowClass = {};

	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WinMessageCallback;
	WindowClass.hInstance = hInstance;

	WindowClass.lpszClassName = "Engine";

	if (!IsUniqueInstance(WindowClass.lpszClassName))
		return 0;

	//GameEngine::Engine::GetInstance().Run();


	if (RegisterClass(&WindowClass))
	{
		HWND WindowHandle = CreateWindowEx(
			0,
			WindowClass.lpszClassName,
			"This is a test",
			WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			hInstance,
			0);

		if (WindowHandle)
		{



			Running = true;
			while (Running)
			{


				MSG Message;
				while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
				{

					if (Message.message == WM_QUIT)
					{
						Running = false;
					}

					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}

			}
		}
		else
		{
			//Handle
		}
	}
	else
	{
		//Handle
	}

	return 0;
}


