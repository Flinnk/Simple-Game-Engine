
#include "GraphicContext.h"
#include "Window.h"

namespace GameEngine {

	GraphicContext::GraphicContext() {}

	GraphicContext::~GraphicContext() {}


	bool GraphicContext::Init(int Width, int Height, const char *Title)
	{
		WindowInstance = new Window();
		if (WindowInstance->Create(Width, Height, Title))
		{
			return true;
		}

		return false;
	}

	void GraphicContext::Update() {

		WindowInstance->Update();
	}

	void GraphicContext::Begin()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GraphicContext::End()
	{
		WindowInstance->SwapDefaultBuffer();
	}

	void GraphicContext::Release() {
		WindowInstance->Terminate();
		delete WindowInstance;
	}

	bool GraphicContext::HasToCLose() {
		if (!WindowInstance)
			return true;
		return WindowInstance->HasToClose();
	}
}
