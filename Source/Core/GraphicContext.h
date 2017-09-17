
#ifndef GRAPHIC_CONTEXT_H
#define GRAPHIC_CONTEXT_H

namespace GameEngine {

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

		struct Vector2 GetDisplaySize();
		const class SpriteRenderer* GetRenderer();

	private:

		class Window* WindowInstance;
		class SpriteRenderer* Renderer = nullptr;
	};

}
#endif // !GRAPHIC_CONTEXT_H
