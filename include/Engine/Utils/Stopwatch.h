#ifndef STOPWATCH_H
#define STOPWATCH_H

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
#endif