#ifndef APPLICATION_H
#define APPLICATION_H

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

#endif // !APPLICATION_H
