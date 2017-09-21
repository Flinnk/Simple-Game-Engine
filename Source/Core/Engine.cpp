#include "Engine.h"
#include "Application.h"
#include "GraphicContext.h"
#include "..\Utils\Time.h"
#include "..\Math\Math.h"
#include <stdio.h>

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
			FrameTime = 0.0f;

			double CurrentTime = Time::GetElapsedSeconds();
			DeltaSeconds = CurrentTime - LastTime;

			FrameTime += DeltaSeconds;
			if (DeltaSeconds < TargetTimePerFrame) {
				float SleepTime = TargetTimePerFrame - DeltaSeconds;
				Wait((TargetTimePerFrame - DeltaSeconds)*1000.0f);
				FrameTime += SleepTime;
			}

			LastTime = Time::GetElapsedSeconds();
		}

		GContext->Release();

		GameInstance->OnEnd();

		delete GContext;
		delete GameInstance;
	}

	void Engine::Wait(float Milliseconds)
	{
		double prevTime = Time::GetElapsedSeconds();
		double nextTime = 0.0;

		while ((nextTime - prevTime) < Milliseconds / 1000.0f) nextTime = Time::GetElapsedSeconds();
	}

	int Engine::GetFpsStat()
	{
		return 1.0f / FrameTime;
	}


	GraphicContext* Engine::GetGraphicContext()
	{
		return GContext;
	}

	Vector2 Engine::GetDisplaySize()
	{
		return GContext->GetDisplaySize();
	}

	void Engine::SetTargetFPS(unsigned int FPS)
	{
		TargetTimePerFrame = 1.0f / FPS;
	}


}