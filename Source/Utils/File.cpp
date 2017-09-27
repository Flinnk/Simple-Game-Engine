#include "File.h"
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace GameEngine
{

	std::string File::ReadFile(std::string Path)
	{
		std::string Content;
		std::ifstream File(Path);
		if (File) {
			std::stringstream Stream;
			Stream << File.rdbuf();
			File.close();
			Content = Stream.str();
		}

		return Content;
	}

	std::string File::GetExecutionDirectory()
	{
#ifdef _WIN32
		HMODULE hModule = GetModuleHandleW(NULL);
		CHAR path[MAX_PATH];
		GetModuleFileName(hModule, path, MAX_PATH);
		std::string Directory(path);
		return Directory;
#else
		return std::string();
#endif

	}

}
