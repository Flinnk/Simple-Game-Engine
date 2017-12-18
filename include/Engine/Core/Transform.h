#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Engine\Math\Vector3.h>

namespace GameEngine
{

	struct Transform
	{
		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;
	};

}
#endif // !TRANSFORM_H
