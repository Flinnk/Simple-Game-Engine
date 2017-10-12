#include "..\..\Utils\Time.h"
#include <Windows.h>

bool Initialized = false;
LARGE_INTEGER Frequency = {};
LARGE_INTEGER BaseCounter = {};

void InitializeSystemTime() {
	Initialized = true;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&BaseCounter);
}

namespace GameEngine {

	double Time::GetCurrentSeconds()
	{
		LARGE_INTEGER Counter;
		QueryPerformanceCounter(&Counter);
		LONGLONG Diff = Counter.QuadPart - BaseCounter.QuadPart;
		return (double)Diff/(double)Frequency.QuadPart;
	}
}
