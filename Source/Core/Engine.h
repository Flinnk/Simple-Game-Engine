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


	private:
		Engine();

		GraphicContext* GContext;
	};

}

#endif // !ENGINE_H
