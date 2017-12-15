#define GLEW_STATIC

#include <Engine\Platform\Windows\WindowsGraphicContext.h>
#include <Engine\Platform\Windows\WindowsOpenGLContext.h>
#include <Engine\Math\Math.h>
#include <Engine\Graphics\Shader.h>
#include <Engine\Renderer\Renderer.h>
#include <Engine\Utils\ResourceManager.h>
#include <Engine\Utils\File.h>
#include <Engine\Renderer\CompiledShaders.h>
#include <Engine\Core\Input.h>
#include <Windowsx.h>

//WS_THICKFRAME Controls resizing
#define WINDOWED_STYLE  ((WS_OVERLAPPEDWINDOW^ WS_THICKFRAME) | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE)
#define FULLSCREEN_STYLE (WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE)


#define ENUM_VALUE(SYMBOL) static_cast<unsigned int>(SYMBOL)

namespace GameEngine {
	extern void CursorPositionCallback(int xpos, int ypos);
	extern void MouseButtonCallback(Mouse button, bool pressed);
	extern void KeyCallback(unsigned int key, bool pressed);
}


LRESULT CALLBACK WinMessageCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	GameEngine::WindowsGraphicContext *Context = (GameEngine::WindowsGraphicContext *)GetWindowLong(Window, GWLP_USERDATA);
	if (Context)
		return Context->ContextMessageCallback(Window, Message, WParam, LParam);

	return DefWindowProc(Window, Message, WParam, LParam);
}


namespace GameEngine {

	WindowsGraphicContext::WindowsGraphicContext()
	{
		CreateKeyMappingTable();
	}

	WindowsGraphicContext::~WindowsGraphicContext()
	{
		Release();
	}

	void WindowsGraphicContext::CreateKeyMappingTable()
	{
		unsigned char StartLetter = ENUM_VALUE(Keyboard::A);
		for (char Letter = 'A'; Letter <= 'Z'; ++Letter)
		{
			VirtualKeyMapping[Letter] = StartLetter++;
		}

		unsigned char StartNumber = ENUM_VALUE(Keyboard::NUM0);
		for (char Number = '0'; Number <= '9'; ++Number)
		{
			VirtualKeyMapping[Number] = StartNumber++;
		}

		VirtualKeyMapping[VK_F1] = ENUM_VALUE(Keyboard::F1);
		VirtualKeyMapping[VK_F2] = ENUM_VALUE(Keyboard::F2);
		VirtualKeyMapping[VK_F3] = ENUM_VALUE(Keyboard::F3);
		VirtualKeyMapping[VK_F4] = ENUM_VALUE(Keyboard::F4);
		VirtualKeyMapping[VK_F5] = ENUM_VALUE(Keyboard::F5);
		VirtualKeyMapping[VK_F6] = ENUM_VALUE(Keyboard::F6);
		VirtualKeyMapping[VK_F7] = ENUM_VALUE(Keyboard::F7);
		VirtualKeyMapping[VK_F8] = ENUM_VALUE(Keyboard::F8);
		VirtualKeyMapping[VK_F9] = ENUM_VALUE(Keyboard::F9);
		VirtualKeyMapping[VK_F10] = ENUM_VALUE(Keyboard::F10);
		VirtualKeyMapping[VK_F11] = ENUM_VALUE(Keyboard::F11);
		VirtualKeyMapping[VK_F12] = ENUM_VALUE(Keyboard::F12);

		VirtualKeyMapping[VK_UP] = ENUM_VALUE(Keyboard::UP_ARROW);
		VirtualKeyMapping[VK_DOWN] = ENUM_VALUE(Keyboard::DOWN_ARROW);
		VirtualKeyMapping[VK_LEFT] = ENUM_VALUE(Keyboard::LEFT_ARROW);
		VirtualKeyMapping[VK_RIGHT] = ENUM_VALUE(Keyboard::RIGHT_ARROW);

		VirtualKeyMapping[VK_BACK] = ENUM_VALUE(Keyboard::BACKSPACE);
		VirtualKeyMapping[VK_SPACE] = ENUM_VALUE(Keyboard::SPACE);
		VirtualKeyMapping[VK_ESCAPE] = ENUM_VALUE(Keyboard::ESCAPE);
		VirtualKeyMapping[VK_TAB] = ENUM_VALUE(Keyboard::TAB);
		VirtualKeyMapping[VK_RETURN] = ENUM_VALUE(Keyboard::ENTER);
		VirtualKeyMapping[VK_LCONTROL] = ENUM_VALUE(Keyboard::LEFT_CONTROL);
		VirtualKeyMapping[VK_RCONTROL] = ENUM_VALUE(Keyboard::RIGHT_CONTROL);
		VirtualKeyMapping[VK_LSHIFT] = ENUM_VALUE(Keyboard::LEFT_SHIFT);
		VirtualKeyMapping[VK_RSHIFT] = ENUM_VALUE(Keyboard::RIGHT_SHIFT);
		VirtualKeyMapping[VK_LMENU] = ENUM_VALUE(Keyboard::LEFT_ALT);
		VirtualKeyMapping[VK_RMENU] = ENUM_VALUE(Keyboard::RIGHT_ALT);

		VirtualKeyMapping[VK_NUMPAD0] = ENUM_VALUE(Keyboard::NUMPAD0);
		VirtualKeyMapping[VK_NUMPAD1] = ENUM_VALUE(Keyboard::NUMPAD1);
		VirtualKeyMapping[VK_NUMPAD2] = ENUM_VALUE(Keyboard::NUMPAD2);
		VirtualKeyMapping[VK_NUMPAD3] = ENUM_VALUE(Keyboard::NUMPAD3);
		VirtualKeyMapping[VK_NUMPAD4] = ENUM_VALUE(Keyboard::NUMPAD4);
		VirtualKeyMapping[VK_NUMPAD5] = ENUM_VALUE(Keyboard::NUMPAD5);
		VirtualKeyMapping[VK_NUMPAD6] = ENUM_VALUE(Keyboard::NUMPAD6);
		VirtualKeyMapping[VK_NUMPAD7] = ENUM_VALUE(Keyboard::NUMPAD7);
		VirtualKeyMapping[VK_NUMPAD8] = ENUM_VALUE(Keyboard::NUMPAD8);
		VirtualKeyMapping[VK_NUMPAD9] = ENUM_VALUE(Keyboard::NUMPAD9);

		VirtualKeyMapping[VK_MULTIPLY] = ENUM_VALUE(Keyboard::MULTIPLY);
		VirtualKeyMapping[VK_ADD] = ENUM_VALUE(Keyboard::ADD);
		VirtualKeyMapping[VK_SEPARATOR] = ENUM_VALUE(Keyboard::SEPARATOR);
		VirtualKeyMapping[VK_SUBTRACT] = ENUM_VALUE(Keyboard::SUBTRACT);
		VirtualKeyMapping[VK_DECIMAL] = ENUM_VALUE(Keyboard::KDECIMAL);
		VirtualKeyMapping[VK_DIVIDE] = ENUM_VALUE(Keyboard::DIVIDE);
		VirtualKeyMapping[VK_NUMLOCK] = ENUM_VALUE(Keyboard::NUMLOCK);

		VirtualKeyMapping[VK_CAPITAL] = ENUM_VALUE(Keyboard::CAPSLOCK);
		VirtualKeyMapping[VK_OEM_COMMA] = ENUM_VALUE(Keyboard::COMMA);
		VirtualKeyMapping[VK_OEM_PERIOD] = ENUM_VALUE(Keyboard::PERIOD);
		VirtualKeyMapping[VK_OEM_MINUS] = ENUM_VALUE(Keyboard::MINUS);
	}


	LRESULT CALLBACK WindowsGraphicContext::ContextMessageCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
	{

		LRESULT Result = 0;

		switch (Message)
		{

		case WM_SIZE:
		{
			Width = LOWORD(LParam);
			Height = HIWORD(LParam);
			if (GraphicBackend)
				GraphicBackend->Resize(Width, Height);
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
			GameEngine::MouseButtonCallback(GameEngine::Mouse::LEFT_BUTTON, Message == WM_LBUTTONDOWN);
			break;
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			GameEngine::MouseButtonCallback(GameEngine::Mouse::MIDDLE_BUTTON, Message == WM_MBUTTONDOWN);
			break;
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			GameEngine::MouseButtonCallback(GameEngine::Mouse::RIGHT_BUTTON, Message == WM_RBUTTONDOWN);
			break;
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYUP:
		{
			unsigned int VKCode = WParam;
			UINT scancode = (LParam & 0x00ff0000) >> 16;
			bool extended = (LParam & 0x01000000) != 0;

			//Handle special keys as windows does not differenciate between left and right key code
			switch (VKCode) {
			case VK_CONTROL:
			{
				VKCode = extended ? VK_RCONTROL : VK_LCONTROL;
				break;
			}
			case VK_SHIFT:
			{
				VKCode = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
				break;
			}
			case VK_MENU:
				VKCode = extended ? VK_RMENU : VK_LMENU;
				break;
			}

			unsigned int CharCode = ::MapVirtualKey(VKCode, MAPVK_VK_TO_CHAR);


			if (VKCode == VK_F4 && (LParam & (1 << 29)))//With 1<<29 we can check if ALT is pressed
			{
				Running = false;

			}
			else
			{
				GameEngine::KeyCallback(VirtualKeyMapping[VKCode], ((LParam & (1 << 31)) == 0));
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


	bool WindowsGraphicContext::Init(const char *Title, DisplayMode Mode, int _Width, int _Height)
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
			DWORD style = 0;
			if (Mode == GameEngine::DisplayMode::FULLSCREEN)
			{
				style = FULLSCREEN_STYLE;
				Width = GetSystemMetrics(SM_CXSCREEN);
				Height = GetSystemMetrics(SM_CYSCREEN);
			}
			else
			{
				style = WINDOWED_STYLE;
			}
			RECT size = { 0, 0, Width, (LONG)Height };
			AdjustWindowRect(&size, style, false);

			WindowHandle = CreateWindow(
				WindowClass.lpszClassName, Title,
				style,
				0,
				0,
				size.right + (-size.left), size.bottom + (-size.top), NULL, NULL, Instance, NULL);

			if (WindowHandle)
			{
				SetWindowLong(WindowHandle, GWLP_USERDATA, (long)this);

				GraphicBackend = new WindowsOpenGLContext(WindowHandle);
				GraphicBackend->Init();
				GraphicBackend->Resize(Width, Height);

				//MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);
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
		if (GraphicBackend)
			GraphicBackend->Clear();
	}

	void WindowsGraphicContext::End()
	{
		if (GraphicBackend)
			GraphicBackend->Display();
		Render->ClearDebugStats();
	}

	void WindowsGraphicContext::Release() {

		ReleaseDC(WindowHandle, DeviceContext);

		if (GraphicBackend) {
			GraphicBackend->Release();
			delete GraphicBackend;
		}

		DestroyWindow(WindowHandle);


		WindowHandle = nullptr;
		DeviceContext = nullptr;
		GraphicBackend = nullptr;

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
			RECT size = { 0, 0, Width, Height };
			AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false);

			return Vector2(size.right + (-size.left), size.bottom + (-size.top));
		}

		return Vector2();
	}

	Renderer* WindowsGraphicContext::GetRenderer()
	{
		return Render;
	}

	void WindowsGraphicContext::SetFullscreen()
	{
		if (WindowHandle != nullptr) {
			SetWindowLong(WindowHandle, GWL_STYLE, FULLSCREEN_STYLE);
			SetWindowPos(WindowHandle, NULL, 0, 0,
				GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
		}
	}

	void WindowsGraphicContext::SetWindowed(int NewWidth, int NewHeight)
	{
		if (WindowHandle != nullptr) {
			Width = NewWidth > 0 ? NewWidth : Width;
			Height = NewHeight > 0 ? NewHeight : Height;
			SetWindowLong(WindowHandle, GWL_STYLE, WINDOWED_STYLE);
			SetWindowPos(WindowHandle, NULL, 0, 0,
				Width, Height,
				SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER|SWP_FRAMECHANGED);
		}
	}
}


