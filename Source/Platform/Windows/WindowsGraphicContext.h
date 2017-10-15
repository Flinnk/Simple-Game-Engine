
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

		bool Init(int Width, int Height, const char *Title) override;
		void Update() override;
		void Begin() override;
		void End() override;
		void Release() override;
		bool HasToCLose() override;

		Vector2 GetDisplaySize() override;
		const Renderer* GetRenderer() override;

	private:
		int Width = 0;
		int Height = 0;
		HWND WindowHandle;
		HDC DeviceContext;
		HGLRC OpenGLContext;
	};
}

#endif // !WINDOWS_GRAPHIC_CONTEXT_H
