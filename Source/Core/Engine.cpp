#include "Engine.h"
#include "Application.h"



namespace GameEngine {

	extern Application* GetApplicationInstance();


	Engine::Engine() {}
	Engine::~Engine(){}

	Engine& Engine::GetInstance()
	{
		static Engine Instance;

		return Instance;
	}

	void Engine::Run()
	{
		Application* GameInstance = GetApplicationInstance();
		GameInstance->OnBegin();
		GameInstance->OnUpdate();
		GameInstance->OnEnd();
		delete GameInstance;

	}

}