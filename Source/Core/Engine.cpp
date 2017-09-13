#include "Engine.h"
#include "Application.h"
#include "GraphicContext.h"
#include "..\Utils\Time.h"

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

		while (!GContext->HasToCLose()) {
			GContext->Update();
			GameInstance->OnUpdate(DeltaSeconds);

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


}