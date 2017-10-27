#ifndef APPLICATION_H
#define APPLICATION_H


namespace GameEngine {

	// Forward declarations
	class Renderer;

	/**
	* Interface that each game must implement to receive the corresping events 
	*/
	class Application
	{

	public:

		/**
		* Default Constructor
		*/
		Application();

		/**
		* Default Destructor
		*/
		virtual ~Application();

		/**
		* Method called from the Engine to initialize Engine components with game's preferences
		*/
		virtual void OnInitialize() = 0;

		/**
		* Method called from the Engine on the first frame of execution, here you should initialize game specific components
		*/
		virtual void OnBegin() = 0;

		/**
		* Method called from the Engine at the beginning of each Update cycle
		*/
		virtual void OnBeginFrame() = 0;

		/**
		* Method called from the Engine during each Update cycle
		* @param DeltaTime The time in seconds it took to complete the last frame
		*/
		virtual void OnUpdate(float DeltaTime) = 0;

		/**
		* Method called from the Engine to start any rendering call
		* @param Renderer Pointer to the Renderer 
		*/
		virtual void OnRender(Renderer* Renderer) = 0;

		/**
		* Method called from the Engine at the end of each Update cycle
		*/
		virtual void OnEndFrame() = 0;

		/**
		* Method called from the Engine at the end of the execution of the game, triggered by the system or the game itself
		*/
		virtual void OnEnd() = 0;
	};
}

#endif // !APPLICATION_H
