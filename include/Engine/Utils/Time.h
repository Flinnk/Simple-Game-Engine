#pragma once 
namespace GameEngine {
	
	/**
	* Class to retrieve time information
	*/
	class Time {
	
	public:

		/**
		* Function that returns the elapsed seconds since the program has started.	
		* @return Elapsed seconds
		*/
		static double GetCurrentSeconds();

	};
}

