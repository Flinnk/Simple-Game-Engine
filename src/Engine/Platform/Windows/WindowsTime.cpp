#include <Engine\Utils\Time.h>
#include <Windows.h>

/* Global Variables */

bool Initialized = false;

/**
* A pointer to a variable that receives the current performance-counter frequency, in counts per second
* @see https://msdn.microsoft.com/es-es/library/windows/desktop/ms644905(v=vs.85).aspx
*/
LARGE_INTEGER Frequency = {};

/**
* Store the performance-counter value, in counts at startup
* @see https://msdn.microsoft.com/es-es/library/windows/desktop/ms644904(v=vs.85).aspx
*/
LARGE_INTEGER BaseCounter = {};

/**
* Function called from Engine to initialize the variables
*/
void InitializeSystemTime()
{
	if (!Initialized) {
		Initialized = true;
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&BaseCounter);
	}
}

namespace GameEngine {

	double Time::GetCurrentSeconds()
	{
		//Get current counts
		LARGE_INTEGER Counter;
		QueryPerformanceCounter(&Counter);

		//Calculate diff with startup counts
		LONGLONG Diff = Counter.QuadPart - BaseCounter.QuadPart;

		return (double)Diff / (double)Frequency.QuadPart;// Counts elpased/(Counts/Seconds) = Seconds elapsed
	}
}
