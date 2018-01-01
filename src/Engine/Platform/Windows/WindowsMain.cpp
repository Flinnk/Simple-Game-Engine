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

void CreateConsole()
{
	AllocConsole();
	SetConsoleTitleA("DebugConsole");
	typedef struct { char* _ptr; int _cnt; char* _base; int _flag; int _file; int _charbuf; int _bufsiz; char* _tmpfname; } FILE_COMPLETE;
	*(FILE_COMPLETE*)stdout = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
	*(FILE_COMPLETE*)stderr = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT), "w");
	*(FILE_COMPLETE*)stdin = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r");
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef ENGINE_DEBUG
	CreateConsole();
#endif
	InitializeSystemTime();
	HANDLE  Mutex = CreateMutex(NULL, true, "SingleInstanceMutex");

	if (!IsUniqueInstance(Mutex, "Engine"))
	{
		ReleaseMutex(Mutex);
		Mutex = NULL;
		return 0;
	}


	GameEngine::Engine::GetInstance().Run();

	ReleaseMutex(Mutex);
	Mutex = NULL;

	return 0;
}


