#ifndef ENGINE_H
#define ENGINE_H


namespace GameEngine {

	class Engine {

	public:

		static Engine& GetInstance();
		virtual ~Engine();

		Engine(Engine const&) = delete;             // Copy construct
		Engine(Engine&&) = delete;                  // Move construct
		Engine& operator=(Engine const&) = delete;  // Copy assign
		Engine& operator=(Engine &&) = delete;      // Move assign

		void Run();
		class GraphicContext* GetGraphicContext();
		struct Vector2 GetDisplaySize();


	private:
		Engine();

		class GraphicContext* GContext;
	};

}

#endif // !ENGINE_H
