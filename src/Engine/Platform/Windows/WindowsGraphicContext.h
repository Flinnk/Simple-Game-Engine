#pragma once 

#include <Engine\Renderer\IGraphicContext.h>
#include <Engine\Renderer\IGraphicBackend.h>
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
		Renderer* GetRenderer() override;
		LRESULT CALLBACK ContextMessageCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);

		void CreateKeyMappingTable();
	private:
		int Width = 0;
		int Height = 0;
		HWND WindowHandle;
		HDC DeviceContext;
		bool Running = true;
		unsigned int VirtualKeyMapping[256];
		GraphicBackend* GraphicBackend=nullptr;
	};
}

