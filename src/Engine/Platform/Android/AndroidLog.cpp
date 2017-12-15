#include <Engine\Utils\Log.h>
#include <android/log.h>
#include <cstdio>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Engine", __VA_ARGS__))

namespace GameEngine
{
	void Log(const char* Text)
	{
		LOGI("%s", Text);
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