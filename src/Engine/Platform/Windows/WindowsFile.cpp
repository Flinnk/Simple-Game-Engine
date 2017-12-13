#include <Engine\Utils\File.h>
#include <Windows.h>

namespace GameEngine {

	std::string File::GetExecutionDirectory()
	{
		HMODULE hModule = GetModuleHandleW(NULL);
		CHAR path[MAX_PATH];
		GetModuleFileName(hModule, path, MAX_PATH);
		std::string Directory(path);
		return Directory;
	}
}