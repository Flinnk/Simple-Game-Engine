
#ifndef GRAPHIC_CONTEXT_H
#define GRAPHIC_CONTEXT_H

namespace GameEngine {

	class Renderer;
	class Window;
	struct Vector2;

	class GraphicContext {

	public:
		GraphicContext();
		~GraphicContext();

		bool Init(int Width, int Height, const char *Title);
		void Update();
		void Begin();
		void End();
		void Release();
		bool HasToCLose();

		Vector2 GetDisplaySize();
		const Renderer* GetRenderer();

	private:

		Window* WindowInstance;
		Renderer* GRenderer = nullptr;
	};

}
#endif // !GRAPHIC_CONTEXT_H
