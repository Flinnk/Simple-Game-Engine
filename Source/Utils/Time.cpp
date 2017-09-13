#include "Time.h"
#include <GLFW\glfw3.h>

namespace GameEngine {

	double Time::GetElapsedSeconds()
	{
		double seconds = glfwGetTime();
		return seconds;
	}
}
