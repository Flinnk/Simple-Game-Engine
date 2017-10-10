#include "WindowsGraphicContext.h"
#include "..\..\Math\Math.h"
#include "..\..\Renderer\Shader.h"
#include "..\..\Renderer\Renderer.h"
#include "..\..\Utils\ResourceManager.h"
#include "..\..\Utils\File.h"
#include "..\..\Renderer\CompiledShaders.h"
#include "..\..\Core\Window.h"


namespace GameEngine {

	WindowsGraphicContext::WindowsGraphicContext() {}

	WindowsGraphicContext::~WindowsGraphicContext()
	{
		Release();
	}


	bool WindowsGraphicContext::Init(int Width, int Height, const char *Title)
	{
		WindowInstance = new Window();
		if (WindowInstance->Create(Width, Height, Title))
		{
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

		return false;
	}

	void WindowsGraphicContext::Update() {

		WindowInstance->Update();
	}

	void WindowsGraphicContext::Begin()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WindowsGraphicContext::End()
	{
		WindowInstance->SwapDefaultBuffer();
	}

	void WindowsGraphicContext::Release() {
		WindowInstance->Terminate();
		delete WindowInstance;

		WindowInstance = nullptr;

		if (Render)
			Render->Release();
		delete Render;
		Render = nullptr;
	}

	bool WindowsGraphicContext::HasToCLose() {
		if (!WindowInstance)
			return true;
		return WindowInstance->HasToClose();
	}

	Vector2 WindowsGraphicContext::GetDisplaySize()
	{
		if (WindowInstance)
			return Vector2(WindowInstance->GetWidth(), WindowInstance->GetHeight());

		return Vector2();
	}

	const Renderer* WindowsGraphicContext::GetRenderer()
	{
		return Render;
	}
}


