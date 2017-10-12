#define GLEW_STATIC

#include "WindowsGraphicContext.h"
#include "..\..\Math\Math.h"
#include "..\..\Renderer\Shader.h"
#include "..\..\Renderer\Renderer.h"
#include "..\..\Utils\ResourceManager.h"
#include "..\..\Utils\File.h"
#include "..\..\Renderer\CompiledShaders.h"
#include <GL\glew.h>
#include <GL\wglew.h>


bool Running = true;

LRESULT CALLBACK WinMessageCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{

	LRESULT Result = 0;

	switch (Message)
	{

	case WM_SIZE:
	{
		//TODO: Handle resize
		break;
	}
	case WM_DESTROY:
	{
		Running = false;
		break;
	}
	case WM_QUIT:
	case WM_CLOSE:
	{
		Running = false;
		break;
	}
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		unsigned int VKCode = WParam;
		/*bool WasDown = ((LParam & (1 << 30)) != 0);
		bool IsDown = ((LParam & (1 << 31)) == 0);

		if (VKCode == 'W')
		{
		if (IsDown)
		OutputDebugStringA("W\n");
		}*/

		if (VKCode == VK_F4 && (LParam & (1 << 29)))//Lcon 1<<29 comprobamos si se ha presionado ALT o no
		{
			Running = false;
		}

		break;
	}

	default:
		Result = DefWindowProc(Window, Message, WParam, LParam);
		break;
	}

	return Result;
}


namespace GameEngine {

	WindowsGraphicContext::WindowsGraphicContext() {}

	WindowsGraphicContext::~WindowsGraphicContext()
	{
		Release();
	}


	bool WindowsGraphicContext::Init(int _Width, int _Height, const char *Title)
	{
		Width = _Width;
		Height = _Height;

		HINSTANCE Instance = GetModuleHandle(NULL);
		WNDCLASS WindowClass = {};

		WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		WindowClass.lpfnWndProc = WinMessageCallback;
		WindowClass.hInstance = Instance;
		WindowClass.hbrBackground = CreateSolidBrush(RGB(0,0,0));

		WindowClass.lpszClassName = "Engine";
		if (RegisterClass(&WindowClass))
		{
			WindowHandle = CreateWindowEx(
				0,
				WindowClass.lpszClassName,
				Title,
				WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE,
				0,
				0,
				Width,
				Height,
				0,
				0,
				Instance,
				0);

			if (WindowHandle)
			{

				PIXELFORMATDESCRIPTOR pfd =
				{
					sizeof(PIXELFORMATDESCRIPTOR),
					1,
					PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
					PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
					32,                        //Colordepth of the framebuffer.
					0, 0, 0, 0, 0, 0,
					0,
					0,
					0,
					0, 0, 0, 0,
					24,                        //Number of bits for the depthbuffer
					8,                        //Number of bits for the stencilbuffer
					0,                        //Number of Aux buffers in the framebuffer.
					PFD_MAIN_PLANE,
					0,
					0, 0, 0
				};

				DeviceContext = GetDC(WindowHandle);
				int  ChosenPixelFormat;
				ChosenPixelFormat = ChoosePixelFormat(DeviceContext, &pfd);
				SetPixelFormat(DeviceContext, ChosenPixelFormat, &pfd);

				HGLRC TempContext = wglCreateContext(DeviceContext);
				wglMakeCurrent(DeviceContext, TempContext);

				glewExperimental = true;
				if (glewInit() != GLEW_OK)
					return false;

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

				//MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);
				glViewport(0, 0, Width, Height);
				Shader* SpriteShader = ResourceManager::GetInstance().LoadShader(std::string(DefaultVertexShader), std::string(DefaultFragmentShader), "SpriteShader");
				Shader* TextShader = ResourceManager::GetInstance().LoadShader(std::string(TextVertexShader), std::string(TextFragmentShader), "TextShader");
				if (SpriteShader && TextShader) {
					Render = new Renderer(SpriteShader, TextShader);
				}
				else {
					return false;
				}
				return true;
			}
			else
			{
				//Handle
			}
		}
		else
		{
			//Handle
		}

		return false;
	}

	void WindowsGraphicContext::Update() {

		MSG Message;
		while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	void WindowsGraphicContext::Begin()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WindowsGraphicContext::End()
	{
		SwapBuffers(DeviceContext);
	}

	void WindowsGraphicContext::Release() {
		ReleaseDC(WindowHandle,DeviceContext);
		DestroyWindow(WindowHandle);
		wglDeleteContext(OpenGLContext);


		WindowHandle = nullptr;
		DeviceContext = nullptr;
		OpenGLContext = nullptr;

		if (Render)
			Render->Release();
		delete Render;
		Render = nullptr;
	}

	bool WindowsGraphicContext::HasToCLose() {
		if (!WindowHandle)
			return true;
		return !Running;
	}

	Vector2 WindowsGraphicContext::GetDisplaySize()
	{
		if (WindowHandle)
			return Vector2(Width, Height);

		return Vector2();
	}

	const Renderer* WindowsGraphicContext::GetRenderer()
	{
		return Render;
	}
}


