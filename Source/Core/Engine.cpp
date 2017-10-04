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
		CurrentApplication = GetApplicationInstance();
		CurrentApplication->OnInitialize();

		CurrentApplication->OnBegin();

		double LastTime = Time::GetElapsedSeconds();
		double DeltaSeconds = 0;

		const Renderer* Renderer = GContext->GetRenderer();
		while (!GContext->HasToCLose()) {
			GContext->Begin();
			GContext->Update();

			CurrentApplication->OnBeginFrame();

			CurrentApplication->OnUpdate(static_cast<float>(DeltaSeconds));

			CurrentApplication->OnRender(Renderer);

			GContext->End();
			FrameTime = 0.0f;

			CurrentApplication->OnEndFrame();

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

		CurrentApplication->OnEnd();

		delete GContext;
		delete CurrentApplication;
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

	Application* Engine::GetRunningApplicationInstance() 
	{
		return CurrentApplication;
	}

}