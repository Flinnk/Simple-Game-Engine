
#include "GraphicContext.h"
#include "Window.h"
#include "..\Math\Math.h"
#include "..\Renderer\Shader.h"
#include "..\Renderer\SpriteRenderer.h"
#include "..\Utils\ResourceManager.h"
#include "..\Utils\File.h"
#include "..\Renderer\CompiledShaders.h"


namespace GameEngine {

	GraphicContext::GraphicContext() {}

	GraphicContext::~GraphicContext() {}


	bool GraphicContext::Init(int Width, int Height, const char *Title)
	{
		WindowInstance = new Window();
		if (WindowInstance->Create(Width, Height, Title))
		{
			Shader* shader = ResourceManager::GetInstance().LoadShader(std::string(DefaultVertexShader), std::string(DefaultFragmentShader), "default_shader");
			if (shader) {
				Renderer = new SpriteRenderer(shader);
			}
			else {
				return false;
			}
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

	Vector2 GraphicContext::GetDisplaySize()
	{
		if (WindowInstance)
			return Vector2(WindowInstance->GetWidth(), WindowInstance->GetHeight());

		return Vector2();
	}

	const SpriteRenderer* GraphicContext::GetRenderer()
	{
		return Renderer;
	}
}


