#include <Engine\Core\Engine.h>
#include <Engine\Renderer\IGraphicContext.h>

#include <Engine\Core\Application.h>

#include <Engine\Utils\Time.h>
#include <Engine\Math\Math.h>

#include <Engine\Audio\SoundManager.h>
#include <Engine\Utils\ResourceManager.h>

#include <Engine\EngineMacros.h>
#include <Engine\Components\ComponentsInclude.h>
#include <Engine\Entities\EntityIncludes.h>


extern void UpdatePlatformInput(); //TODO: Maybe create an IPlatform class to handle platofrm specific events

namespace GameEngine {

	extern Application* GetApplicationInstance(); //Implemented in Game project
	extern IGraphicContext* CreateGraphicContext();

	Engine::Engine() {}
	Engine::~Engine() {}

	Engine& Engine::GetInstance()
	{
		static Engine Instance;

		return Instance;
	}

	void Engine::ExecuteEngine()
	{
		if (Init())
		{
			Run();
		}
		else
		{
			//Show log
		}

		Release();
	}

	bool Engine::Init()
	{
		RegisterFactoryTypes();

		if (!SoundManager::GetInstance().Init())
			return false;

		GraphicContext = CreateGraphicContext();
		if (GraphicContext == nullptr)
			return false;

		CurrentApplication = GetApplicationInstance();
		if (CurrentApplication == nullptr)
			return false;
		CurrentApplication->OnInitialize();

		return true;
	}

	//Main Loop
	void Engine::Run()
	{

		double LastTime = Time::GetCurrentSeconds();
		double DeltaSeconds = 0;

		Renderer* Renderer = GraphicContext->GetRenderer();

		CurrentApplication->OnBegin();

		//Execution Loop
		while (!GraphicContext->HasToCLose() && !CloseEngine) {

			//Frame Begin
			UpdatePlatformInput();
			GraphicContext->Begin();
			GraphicContext->Update();

			CurrentApplication->OnBeginFrame();

			//Frame Update
			CurrentApplication->OnUpdate(static_cast<float>(DeltaSeconds));
			CurrentApplication->OnRender(Renderer);

			//Frame End
			GraphicContext->End();
			FrameTime = 0.0f;

			CurrentApplication->OnEndFrame();

			double CurrentTime = Time::GetCurrentSeconds();
			DeltaSeconds = CurrentTime - LastTime;

			FrameTime += DeltaSeconds;
			if (DeltaSeconds < TargetTimePerFrame) {
				double SleepTime = TargetTimePerFrame - DeltaSeconds;
				Wait((SleepTime));
				FrameTime += SleepTime;
			}

			CurrentTime = Time::GetCurrentSeconds();
			DeltaSeconds += CurrentTime - LastTime;
			LastTime = Time::GetCurrentSeconds();

		}
	}

	void Engine::Release()
	{
		//Resource release
		SoundManager::GetInstance().Release();
		ResourceManager::GetInstance().Clear();

		if (CurrentApplication != nullptr)
			CurrentApplication->OnEnd();

		delete CurrentApplication;

		if (GraphicContext != nullptr)
			GraphicContext->Release();

		delete GraphicContext;

	}

	void Engine::Wait(double Seconds)
	{
		double prevTime = Time::GetCurrentSeconds();
		double nextTime = 0.0;

		while ((nextTime - prevTime) < Seconds) nextTime = Time::GetCurrentSeconds();
	}

	int Engine::GetFpsStat()
	{
		return static_cast<int>(ceil(1.0 / FrameTime));
	}


	IGraphicContext* Engine::GetGraphicContext()
	{
		return GraphicContext;
	}

	Vector2 Engine::GetDisplaySize()
	{
		return GraphicContext->GetDisplaySize();
	}

	void Engine::SetTargetFPS(unsigned int FPS)
	{
		if (FPS == 0)
			FPS = 1;
		TargetTimePerFrame = 1.0f / FPS;
	}

	Application* Engine::GetRunningApplicationInstance()
	{
		return CurrentApplication;
	}

	void Engine::Exit()
	{
		CloseEngine = true;
	}

	void Engine::RegisterFactoryTypes()
	{
		RegisterToFactory(SceneComponent);
		RegisterToFactory(CameraComponent);
		RegisterToFactory(SpriteComponent);

		RegisterToFactory(Entity);
		RegisterToFactory(CameraEntity);
		RegisterToFactory(Free3DCamera);

	}

}