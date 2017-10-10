#ifndef IGRAPHIC_CONTEXT_H
#define IGRAPHIC_CONTEXT_H

namespace GameEngine {

	class Renderer;
	struct Vector2;

	class IGraphicContext {

	public:

		virtual bool Init(int Width, int Height, const char *Title) = 0;
		virtual void Update() = 0;
		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Release() = 0;
		virtual bool HasToCLose() = 0;

		virtual Vector2 GetDisplaySize() = 0;
		virtual const Renderer* GetRenderer() = 0;

	protected:

		Renderer* Render = nullptr;
	};

}
#endif // !IGRAPHIC_CONTEXT_H
