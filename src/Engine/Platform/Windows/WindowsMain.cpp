#include <Windows.h>
#include <Engine\Core\Engine.h>
#include <Engine\Renderer\IGraphicContext.h>
#include <Engine\Platform\Windows\WindowsGraphicContext.h>

#include <io.h>
#include <fcntl.h>
#include <iostream>
extern void InitializeSystemTime();
namespace GameEngine {

	IGraphicContext* CreateGraphicContext()
	{
		return new WindowsGraphicContext();
	}
}

bool IsUniqueInstance(HANDLE Mutex, LPCSTR WindowClassName)
{
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND Window = FindWindow(WindowClassName, NULL);
		if (Window)
		{
			ShowWindow(Window, SW_SHOWNORMAL);
			SetFocus(Window);
			SetForegroundWindow(Window);
			SetActiveWindow(Window);
		}
		return false;
	}

	return true;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	InitializeSystemTime();
	HANDLE  Mutex = CreateMutex(NULL, true, "SingleInstanceMutex");

	if (!IsUniqueInstance(Mutex, "Engine"))
	{
		ReleaseMutex(Mutex);
		Mutex = NULL;
		return 0;
	}


	GameEngine::Engine::GetInstance().ExecuteEngine();

	ReleaseMutex(Mutex);
	Mutex = NULL;

	return 0;
}


