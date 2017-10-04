#ifndef ENGINE_H
#define ENGINE_H


namespace GameEngine {

	class GraphicContext;
	struct Vector2;
	class Application;

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

		Application* GetRunningApplicationInstance();


	private:
		Engine();

		float TargetTimePerFrame = (1.0f/60.0f);
		int CurrentFPS=0;
		double FrameTime = 0;
		void Wait(double Milliseconds);
		GraphicContext* GContext;
		Application* CurrentApplication;
	};

}

#endif // !ENGINE_H
