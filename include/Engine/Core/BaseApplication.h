#ifndef BASE_APPLICATION_H
#define BASE_APPLICATION_H

#include <Engine\Core\Application.h>

namespace GameEngine {


	class Scene;

	class BaseApplication : public Application 
	{
	public:
		BaseApplication();
		virtual ~BaseApplication();

		virtual void OnInitialize() override;
		virtual void OnBegin() override;
		virtual void OnBeginFrame() override;
		virtual void OnUpdate(float DeltaSeconds) override;
		virtual void OnRender(class GameEngine::Renderer* Renderer) override;
		virtual void OnEndFrame() override;

		virtual void OnEnd() override;

		void LoadScene(Scene* NewScene);
	protected:

		Scene* CurrentScene = nullptr;
		Scene* NextScene = nullptr;
	};
}
#endif // !BASE_APPLICATION_H
