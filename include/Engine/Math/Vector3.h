#pragma once

namespace GameEngine {

	struct Vector2;

	struct Vector3 {
		union
		{
			struct { float x, y, z; };
			float elements[3];
		};
		Vector3();
		Vector3(float _x, float _y, float _z);
		Vector3(const Vector2& vector);

		Vector3 operator*(float scalar) const;
		Vector3 operator*(const Vector3& rhs) const;

		Vector3 operator+(const Vector3& rhs) const;
		Vector3 operator-(const Vector3& rhs) const;
		Vector3& operator=(const Vector2& vector);

		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);

		Vector3 Normalize();
		float Length();

		static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
		static float Dot(const Vector3& lhs, const Vector3& rhs);
	};
}



