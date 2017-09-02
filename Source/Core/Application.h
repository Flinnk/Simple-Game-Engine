

namespace GameEngine {

	class Application
	{

	public:

		Application();
		virtual ~Application();

		virtual void OnBegin() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEnd() = 0;
	};
}