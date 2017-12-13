#ifndef ASSERT_H
#define ASSERT_H

#include <Engine\Utils\Log.h>

namespace GameEngine
{

	#ifdef ASSERT_ENABLE

	#define DebugBreak() __asm {int 3}

	#define ASSERT(expr) \
		if(expr){} \
		else \
		{ \
			GameEngine::LogFormat("Assert %s Failed at: %s at line %d",#expr,__FILE__,__LINE__); \
			DebugBreak(); \
		}
	#else 

	#define ASSERT(expr)

	#endif
}

#endif // !ASSERT_H
