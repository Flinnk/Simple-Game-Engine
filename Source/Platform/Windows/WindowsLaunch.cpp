#include <Windows.h>
#include "..\..\Core\Engine.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameEngine::Engine::GetInstance().Run();
	return 0;
}


