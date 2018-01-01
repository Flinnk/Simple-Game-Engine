#pragma once 

#include <Engine\Utils\Log.h>
#include <Engine\Utils\Assert.h>
#include <string>
#ifdef _WIN32
#include <GL\glew.h>
#endif // _WIN32
namespace GameEngine
{
	bool GLCheckError(const char *file, int line);

#ifdef ENGINE_DEBUG

#define GLCall(x) \
	x;\
	ASSERT(GLCheckError(__FILE__,__LINE__));
	
#else
#define GLCall(x) x;

#endif
}
