#include "Log.h"
#include <ctime>
#include <cstdio>
#include <cstdarg>

namespace GameEngine
{
	void Log(const char* Text)
	{
		time_t CurrentTime = time(0); //Current time
		struct tm Now;
		localtime_s(&Now, &CurrentTime);
		char TimeBuffer[1024];
		sprintf_s(TimeBuffer, "%d-%d-%d %d:%d:%d", Now.tm_mday, Now.tm_mon + 1, Now.tm_year + 1900, Now.tm_hour, Now.tm_min, Now.tm_sec);
		printf(TimeBuffer);
		printf(" ");
		printf(Text);
		printf("\n");
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