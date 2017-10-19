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
#include "..\..\Core\Input.h"
#include <Windowsx.h>


namespace GameEngine {
	extern void CursorPositionCallback(int xpos, int ypos);
	extern void MouseButtonCallback(int button, bool pressed);
	extern void KeyCallback(int key, bool pressed);
}

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
	case WM_QUIT:
	case WM_CLOSE:
	{
		Running = false;
		break;
	}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		GameEngine::MouseButtonCallback(MOUSE_BUTTON_LEFT, Message == WM_LBUTTONDOWN);
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		GameEngine::MouseButtonCallback(MOUSE_BUTTON_MIDDLE, Message == WM_MBUTTONDOWN);
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		GameEngine::MouseButtonCallback(MOUSE_BUTTON_RIGHT, Message == WM_RBUTTONDOWN);
		break;
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
		unsigned int VKCode = WParam;
		GameEngine::KeyCallback(VKCode, ((LParam & (1 << 31)) == 0));
		GameEngine::KeyCallback(KEY_ALT, ((LParam & (1 << 31)) == 0));

		if (VKCode == VK_F4 && (LParam & (1 << 29)))//With 1<<29 we can check if ALT is pressed
		{
			Running = false;
		}

		break;
	}

	case WM_MOUSEMOVE:
	{
		GameEngine::CursorPositionCallback(GET_X_LPARAM(LParam), GET_Y_LPARAM(LParam));
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
		WindowClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

		WindowClass.lpszClassName = "Engine";
		if (RegisterClass(&WindowClass))
		{
			RECT size = { 0, 0, Width, (LONG)Height };
			AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false);

			WindowHandle = CreateWindow(
				WindowClass.lpszClassName, Title,
				WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |WS_VISIBLE,
				GetSystemMetrics(SM_CXSCREEN) / 2 - Width / 2,
				GetSystemMetrics(SM_CYSCREEN) / 2 - Height / 2,
				size.right + (-size.left), size.bottom + (-size.top), NULL, NULL, Instance, NULL);

			if (WindowHandle)
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
		ReleaseDC(WindowHandle, DeviceContext);
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
		if (WindowHandle) {
			RECT size = { 0, 0, Width, (LONG)Height };
			AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false);
			
			return Vector2(size.right + (-size.left), size.bottom + (-size.top));
		}

		return Vector2();
	}

	const Renderer* WindowsGraphicContext::GetRenderer()
	{
		return Render;
	}
}


