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

	//Main Loop
	void Engine::Run()
	{

		//Initialization
		RegisterFactoryTypes();

		GraphicContext = CreateGraphicContext();
		SoundManager::GetInstance().Init();
		CurrentApplication = GetApplicationInstance();
		CurrentApplication->OnInitialize();

		CurrentApplication->OnBegin();

		double LastTime = Time::GetCurrentSeconds();
		double DeltaSeconds = 0;

		Renderer* Renderer = GraphicContext->GetRenderer();

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

		//Resource release
		SoundManager::GetInstance().Release();
		ResourceManager::GetInstance().Clear();
		GraphicContext->Release();

		CurrentApplication->OnEnd();

		delete GraphicContext;
		delete CurrentApplication;
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