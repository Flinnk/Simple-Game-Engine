#pragma once 

#include <Engine\Utils\Log.h>

namespace GameEngine
{

	#ifdef ENGINE_DEBUG

	#define DebugBreak() __asm {int 3}

	#define ASSERT(expr) \
		if(expr){} \
		else \
		{ \
			GameEngine::LogFormat("Assert %s Failed at: %s at line %d\n",#expr,__FILE__,__LINE__); \
			DebugBreak(); \
		}
	#else 

	#define ASSERT(expr)

	#endif
}

