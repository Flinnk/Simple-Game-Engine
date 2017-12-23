#pragma once 

namespace GameEngine {

	class Stopwatch {
	public:

		Stopwatch();

		double GetElapsedSeconds();
		void Restart();

	private:
		double StartTime = 0;
	};
}
