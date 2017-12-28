#pragma once 

#include <Engine\Math\Matrix4.h>

namespace GameEngine
{
	enum class CameraMode : unsigned char
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};

	struct Camera
	{
	public:
		CameraMode Mode;

		//2D
		//TODO: OrthographicSize

		//3D
		float FieldOfView=90.0f;
		float AspectRatio;

		//BOTH
		float NearPlane = -1.0f;
		float FarPlane = 1000.0f;
	};

}
