#define GLEW_STATIC


#include <Engine\Platform\Windows\WindowsOpenGLContext.h>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\wglew.h>
#include <Engine\Core\Engine.h>
#include <Engine\Math\Vector2.h>

namespace GameEngine
{

	WindowsOpenGLContext::WindowsOpenGLContext(HWND WindowHandle)
	{
		this->WindowHandle = WindowHandle;
	}

	bool WindowsOpenGLContext::Init()
	{
		PIXELFORMATDESCRIPTOR pfd = {};
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.cAuxBuffers = 0;
		pfd.iLayerType = PFD_MAIN_PLANE;

		DeviceContext = GetDC(WindowHandle);
		int  ChosenPixelFormat;
		ChosenPixelFormat = ChoosePixelFormat(DeviceContext, &pfd);
		SetPixelFormat(DeviceContext, ChosenPixelFormat, &pfd);

		HGLRC TempContext = wglCreateContext(DeviceContext);
		wglMakeCurrent(DeviceContext, TempContext);

		glewExperimental = true;
		if (glewInit() != GLEW_OK)
			return false;
		glGetError();
		int attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB, 0,
			0
		};

		if (wglewIsSupported("WGL_ARB_create_context") == 1)
		{
			OpenGLContext = wglCreateContextAttribsARB(DeviceContext, 0, attribs);
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(TempContext);
			wglMakeCurrent(DeviceContext, OpenGLContext);
		}


		Vector2 Size = Engine::GetInstance().GetDisplaySize();
		glViewport(0, 0, Size.x, Size.y);

		//glEnable(GL_DEPTH_TEST);
		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

		return true;
	}

	void WindowsOpenGLContext::Resize(int Width, int Height)
	{
		glViewport(0, 0, Width, Height);
	}


	void WindowsOpenGLContext::Clear()
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void WindowsOpenGLContext::Display()
	{
		SwapBuffers(DeviceContext);
	}

	//TODO: Test
	void WindowsOpenGLContext::Release()
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(OpenGLContext);
	}

}