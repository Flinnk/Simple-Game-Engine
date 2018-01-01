#include <Engine\Graphics\OpenGL.h>
namespace GameEngine
{
	bool GLCheckError(const char *file, int line)
	{
		GLenum errorCode;
		while ((errorCode = glGetError()) != GL_NO_ERROR)
		{
			LogFormat("[OPENGL] error %s at: %s (%d)\n", std::to_string(errorCode).c_str(), file, line);
			return false;
		}
		return true;
	}
}