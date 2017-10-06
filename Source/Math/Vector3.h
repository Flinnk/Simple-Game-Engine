#ifndef VECTOR3_H
#define VECTOR3_H

namespace GameEngine {

	struct Vector3 {
		float x, y, z;
		Vector3();
		Vector3(float _x, float _y, float _z);

		Vector3 operator*(float scalar);
	};
}

#endif // !VECTOR3_H

