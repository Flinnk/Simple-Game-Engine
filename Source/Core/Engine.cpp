#include "Engine.h"
#include "Application.h"
#include "GraphicContext.h"
#include "..\Utils\Time.h"
#include "..\Math\Math.h"
#include <stdio.h>
#include "..\Audio\SoundManager.h"

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
		SoundManager::GetInstance().Init();
		Application* GameInstance = GetApplicationInstance();
		GameInstance->OnInitialize();

		GameInstance->OnBegin();

		double LastTime = Time::GetElapsedSeconds();
		double DeltaSeconds = 0;

		const SpriteRenderer* Renderer = GContext->GetRenderer();
		while (!GContext->HasToCLose()) {
			GContext->Begin();

			GContext->Update();
			GameInstance->OnUpdate(static_cast<float>(DeltaSeconds));

			GameInstance->OnRender(Renderer);

			GContext->End();
			FrameTime = 0.0f;

			double CurrentTime = Time::GetElapsedSeconds();
			DeltaSeconds = CurrentTime - LastTime;

			FrameTime += DeltaSeconds;
			if (DeltaSeconds < TargetTimePerFrame) {
				double SleepTime = TargetTimePerFrame - DeltaSeconds;
				Wait((TargetTimePerFrame - DeltaSeconds)*1000.0f);
				FrameTime += SleepTime;
			}

			CurrentTime = Time::GetElapsedSeconds();
			DeltaSeconds += CurrentTime - LastTime;
			LastTime = Time::GetElapsedSeconds();

		}

		GContext->Release();
		SoundManager::GetInstance().Release();

		GameInstance->OnEnd();

		delete GContext;
		delete GameInstance;
	}

	void Engine::Wait(double Milliseconds)
	{
		double prevTime = Time::GetElapsedSeconds();
		double nextTime = 0.0;

		while ((nextTime - prevTime) < Milliseconds / 1000.0f) nextTime = Time::GetElapsedSeconds();
	}

	int Engine::GetFpsStat()
	{
		return static_cast<int>(1.0 / FrameTime);
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