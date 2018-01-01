#pragma once 

namespace GameEngine {

	/* Forward Declarations */
	class IGraphicContext;
	struct Vector2;
	class Application;

	/**
	* Class which controls the game application execution and the components
	*/
	class Engine {

	public:

		/**
		* Obtains the unique Engine class instance
		* @return Reference to the Engine instance
		*/
		static Engine& GetInstance();

		/* Deleted Methods */

		Engine(Engine const&) = delete;             // Copy construct
		Engine(Engine&&) = delete;                  // Move construct
		Engine& operator=(Engine const&) = delete;  // Copy assign
		Engine& operator=(Engine &&) = delete;      // Move assign

		/**
		* Starts the execution of the Main Loop, this method should not be called by the Game
		*/
		void Run();

		/**
		* Ends the execution of the Engine, freeing resources and calling OnEnd method of the running game
		*/
		void Exit();

		/**
		* Returns a pointer to the current graphic context, game should not free or delete the pointer
		* @return Pointer to the current graphic context
		*/
		IGraphicContext* GetGraphicContext();

		/**
		* Returns a pointer to the running Application instance passed from the game, game should not free or delete the pointer
		* @return Pointer to the running Application instance passed from the game
		*/
		Application* GetRunningApplicationInstance();

		/**
		* Returns the FPS based on the last frame duration
		* @return Current FPS
		*/
		int GetFpsStat();

		/**
		* Locks the execution of the game to the specified frames per second
		* @param FPS Frames per second
		*/
		void SetTargetFPS(unsigned int FPS);


		/**
		* Returns the current window size
		* @return Current Display Size, X=Width and Y=Height
		*/
		Vector2 GetDisplaySize();



	private:

		/**
		* Default constructor
		*/
		Engine();

		/**
		* Default destructor
		*/
		~Engine();

		/**
		* Wait for the next frame using a lazy loop
		* @param Seconds Seconds to wait
		*/
		void Wait(double Seconds);

		void RegisterFactoryTypes();

		/** Target time in milliseconds for the duration of the frame lock */
		double TargetTimePerFrame = (1.0f/60.0f);

		/** Current running FPS stat based ont the previous frame duration */
		int CurrentFPS=0;

		/** Total duration of the frame */
		double FrameTime = 1;

		/** Pointer to the current graphic context provided from the platform layer */
		IGraphicContext* GraphicContext;

		/** Pointer to the current running game application */
		Application* CurrentApplication;

		/** Flag for ending the engine execution */
		bool CloseEngine = false;
	};

}
