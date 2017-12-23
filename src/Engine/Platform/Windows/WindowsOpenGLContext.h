#pragma once 

#include <Engine\Renderer\IGraphicBackend.h>
#include <Windows.h>

namespace GameEngine 
{

	class WindowsOpenGLContext : public GraphicBackend
	{
	public:
		WindowsOpenGLContext(HWND WindowHandle);
		bool Init() override;
		void Clear() override;
		void Resize(int Width, int Height) override;
		void Display() override;
		void Release() override;
	private:
		HWND WindowHandle;
		HGLRC OpenGLContext;
		HDC DeviceContext;
	};

}
