
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

	private:
		Engine();
	};

}