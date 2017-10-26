
#ifndef WINDOWS_GRAPHIC_CONTEXT_H
#define WINDOWS_GRAPHIC_CONTEXT_H

#include "..\..\Renderer\IGraphicContext.h"
#include <Windows.h>


namespace GameEngine {

	class WindowsGraphicContext : public IGraphicContext
	{

	public:

		WindowsGraphicContext();
		~WindowsGraphicContext();

		bool Init(const char *Title, DisplayMode Mode, int Width, int Height) override;
		void Update() override;
		void Begin() override;
		void End() override;
		void Release() override;
		bool HasToCLose() override;

		void SetFullscreen()override;
		void SetWindowed(int Width = 0, int Height = 0)override;

		Vector2 GetDisplaySize() override;
		const Renderer* GetRenderer() override;
		LRESULT CALLBACK ContextMessageCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);


	private:
		int Width = 0;
		int Height = 0;
		HWND WindowHandle;
		HDC DeviceContext;
		HGLRC OpenGLContext;
		bool Running = true;
	};
}

#endif // !WINDOWS_GRAPHIC_CONTEXT_H
