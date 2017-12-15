#include <Engine\Utils\Stopwatch.h>
#include <Engine\Utils\Time.h>

namespace GameEngine {

	Stopwatch::Stopwatch():StartTime(Time::GetCurrentSeconds())
	{

	}

	double Stopwatch::GetElapsedSeconds()
	{
		return Time::GetCurrentSeconds() - StartTime;
	}

	void Stopwatch::Restart()
	{
		StartTime = Time::GetCurrentSeconds();
	}
}