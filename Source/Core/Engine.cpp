#include "Engine.h"
#include "Application.h"
#include "GraphicContext.h"
#include "..\Utils\Time.h"
#include "..\Math\Math.h"

namespace GameEngine {

	extern Application* GetApplicationInstance();


	Engine::Engine() {}
	Engine::~Engine() {}

	Engine& Engine::GetInstance()
	{
		static Engine Instance;

		return Instance;
	}

	void Engine::Run()
	{
		GContext = new GraphicContext();
		Application* GameInstance = GetApplicationInstance();
		GameInstance->OnInitialize();

		GameInstance->OnBegin();

		double LastTime = Time::GetElapsedSeconds();
		double DeltaSeconds = 0;

		const SpriteRenderer* Renderer = GContext->GetRenderer();
		while (!GContext->HasToCLose()) {
			GContext->Begin();

			GContext->Update();
			GameInstance->OnUpdate(DeltaSeconds);

			GameInstance->OnRender(Renderer);

			GContext->End();

			double CurrentTime = Time::GetElapsedSeconds();
			DeltaSeconds = CurrentTime - LastTime;
			LastTime = CurrentTime;
		}

		GContext->Release();

		GameInstance->OnEnd();

		delete GContext;
		delete GameInstance;
	}

	GraphicContext* Engine::GetGraphicContext() 
	{
		return GContext;
	}

	Vector2 Engine::GetDisplaySize()
	{
		return GContext->GetDisplaySize();
	}


}