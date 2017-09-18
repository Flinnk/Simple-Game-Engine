#include "Time.h"
#include <GLFW\glfw3.h>

namespace GameEngine {

	float Time::GetElapsedSeconds()
	{
		return static_cast<float>(glfwGetTime());
	}
}
