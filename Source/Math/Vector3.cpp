#include "Vector3.h"

namespace GameEngine 
{
	Vector3& Vector3::operator*(float scalar)
	{
		return Vector3(x*scalar, y*scalar, z*scalar);
	}


	Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
}