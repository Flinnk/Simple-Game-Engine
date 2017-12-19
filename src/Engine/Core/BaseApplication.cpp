#include <Engine\Core\BaseApplication.h>
#include <Engine\Core\Scene.h>
#include <Engine\Audio\SoundManager.h>

namespace GameEngine {
	BaseApplication::BaseApplication()
	{

	}
	BaseApplication::~BaseApplication()
	{
		if (CurrentScene)
			delete CurrentScene;
		CurrentScene = nullptr;

		if (NextScene)
			delete NextScene;
		NextScene = nullptr;
	}

	void BaseApplication::OnInitialize()
	{

	}

	void BaseApplication::OnBegin()
	{
		CurrentScene->OnEnter();
	}

	void BaseApplication::OnBeginFrame()
	{
		if (NextScene != nullptr)
		{
			if (CurrentScene)
			{
				CurrentScene->OnExit();
				delete CurrentScene;
				CurrentScene = nullptr;
			}
			SoundManager::GetInstance().StopAll();//TODO: Revise when own implementation is done

			CurrentScene = NextScene;
			CurrentScene->OnEnter();
			NextScene = nullptr;
		}
	}

	void BaseApplication::OnUpdate(float DeltaSeconds)
	{
		CurrentScene->OnUpdate(DeltaSeconds);
	}

	void BaseApplication::OnRender(class GameEngine::Renderer* Renderer)
	{
		CurrentScene->OnRender(Renderer);
	}

	void BaseApplication::OnEndFrame()
	{

	}

	void BaseApplication::OnEnd()
	{
		
	}

	void BaseApplication::LoadScene(Scene* NewScene)
	{
		NextScene = NewScene;
	}
}