#ifndef WINDOW_H
#define WINDOW_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace GameEngine {

	class Window {

	public:
		Window();

		bool Create(int Width, int Height, const char *Title);
		void Update();
		void Terminate();
		void SwapDefaultBuffer();
		bool HasToClose();
		~Window();

		int GetWidth();
		int GetHeight();

	private:
		int Width;
		int Height;
		void Resize(int NewWidth, int NewHeight);
		static void ResizeCallback(struct GLFWwindow* window, int width, int height);

		GLFWwindow* WindowInstance;
	};

}
#endif // !WINDOW_H


