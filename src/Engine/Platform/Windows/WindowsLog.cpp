#include <Engine\Utils\Log.h>
#include <cstdio>
#include <cstdarg>
#include <Windows.h>
#include <iostream>

namespace GameEngine
{
	void Log(const char* Text)
	{
		OutputDebugStringA(Text);
		std::cout << Text << std::endl;
	}

	void LogFormat(const char* Text, ...)
	{
		char Buffer[2048];

		va_list valist;
		va_start(valist, Text);
		vsnprintf(Buffer, 2048, Text, valist);
		va_end(valist);
		Log(Buffer);
	}
}