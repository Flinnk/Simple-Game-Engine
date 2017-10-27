#ifndef IGRAPHIC_CONTEXT_H
#define IGRAPHIC_CONTEXT_H

namespace GameEngine {

	class Renderer;
	struct Vector2;

	enum DisplayMode {
		WINDOWED, FULLSCREEN
	};


	class IGraphicContext {

	public:

		virtual bool Init(const char *Title, DisplayMode Mode = DisplayMode::WINDOWED, int Width = 0, int Height = 0) = 0;
		virtual void Update() = 0;
		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void Release() = 0;
		virtual bool HasToCLose() = 0;

		virtual void SetFullscreen()=0;
		virtual void SetWindowed(int Width = 0, int Height = 0)=0;

		virtual Vector2 GetDisplaySize() = 0;
		virtual Renderer* GetRenderer() = 0;

	protected:

		Renderer* Render = nullptr;
	};

}
#endif // !IGRAPHIC_CONTEXT_H
