#define GLEW_STATIC

#include "Window.h"


namespace GameEngine {

	extern void CursorPositionCallback(double xpos, double ypos);
	extern void KeyCallback(int key, bool pressed);
	extern void MouseButtonCallback(int button, bool pressed);

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		CursorPositionCallback(xpos, ypos);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		KeyCallback(key, action != GLFW_RELEASE);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		MouseButtonCallback(button, action != GLFW_RELEASE);
	}

	void Window::ResizeCallback(GLFWwindow* window, int width, int height) {
		Window* WindowPointer = static_cast<Window*>(glfwGetWindowUserPointer(window));
		WindowPointer->Resize(width, height);
		glViewport(0, 0, width, height);
	}

	void Window::Resize(int NewWidth, int NewHeight) {
		Width = NewWidth;
		Height = NewHeight;
	}


	Window::Window() :Width(0), Height(0) {}

	Window::~Window() {}

	bool Window::Create(int Width, int Height, const char* Title)
	{
		if (!glfwInit())
			return false;

		this->Width = Width;
		this->Height = Height;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		WindowInstance = glfwCreateWindow(Width, Height, Title, NULL, NULL);
		if (!WindowInstance) {
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(WindowInstance);

		glfwSetWindowUserPointer(WindowInstance, this);

		glfwSetFramebufferSizeCallback(WindowInstance, ResizeCallback);
		glfwSetKeyCallback(WindowInstance, key_callback);
		glfwSetCursorPosCallback(WindowInstance, cursor_position_callback);
		glfwSetMouseButtonCallback(WindowInstance, mouse_button_callback);
		
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
			return false;


		return true;
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::SwapDefaultBuffer()
	{
		glfwSwapBuffers(WindowInstance);
	}



	void Window::Terminate() {
		glfwTerminate();
	}

	bool Window::HasToClose() {
		return glfwWindowShouldClose(WindowInstance);
	}

	int Window::GetWidth()
	{
		return Width;
	}

	int Window::GetHeight()
	{
		return Height;
	}
}
