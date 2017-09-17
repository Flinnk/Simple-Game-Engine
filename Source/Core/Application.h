#ifndef APPLICATION_H
#define APPLICATION_H


namespace GameEngine {

	class SpriteRenderer;

	class Application
	{

	public:

		Application();
		virtual ~Application();

		virtual void OnInitialize() = 0;
		virtual void OnBegin() = 0;
		virtual void OnUpdate(float DeltaTime) = 0;
		virtual void OnRender(const SpriteRenderer* Renderer) = 0;
		virtual void OnEnd() = 0;
	};
}

#endif // !APPLICATION_H
