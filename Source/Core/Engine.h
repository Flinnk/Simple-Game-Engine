#ifndef ENGINE_H
#define ENGINE_H


namespace GameEngine {

	class GraphicContext;
	struct Vector2;

	class Engine {

	public:

		static Engine& GetInstance();
		virtual ~Engine();

		Engine(Engine const&) = delete;             // Copy construct
		Engine(Engine&&) = delete;                  // Move construct
		Engine& operator=(Engine const&) = delete;  // Copy assign
		Engine& operator=(Engine &&) = delete;      // Move assign

		void Run();
		GraphicContext* GetGraphicContext();
		Vector2 GetDisplaySize();

		void SetTargetFPS(unsigned int FPS);
		int GetFpsStat();
	private:
		Engine();

		float TargetTimePerFrame = (1.0f/60.0f);
		int CurrentFPS=0;
		float FrameTime = 0;
		void Wait(float Milliseconds);
		GraphicContext* GContext;
	};

}

#endif // !ENGINE_H
