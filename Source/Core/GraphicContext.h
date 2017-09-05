
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

	private:

		class Window* WindowInstance;
	};

}
#endif // !GRAPHIC_CONTEXT_H
