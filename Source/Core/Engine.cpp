#include "Engine.h"
#include "Application.h"
#include "GraphicContext.h"


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
		while (!GContext->HasToCLose()) {
			GContext->Update();
			GameInstance->OnUpdate();
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