#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include <math.h>

namespace GameEngine
{

#define PI 3.14159265359f

	inline float ClampFloat(float Value, float Min, float Max)
	{
		//TODO: Make own implementation of min function and max function
		return fmaxf(Min, fminf(Value, Max));

	}

	inline float ToRadians(float Degrees)
	{
		return Degrees * (PI / 180.0f);
	}
}

#endif // !MATH_UTILS_H
