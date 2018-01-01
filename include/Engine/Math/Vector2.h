#pragma once

namespace GameEngine
{
	struct Vector3;

	struct Vector2 {
		union
		{
			struct { float x, y; };
			float elements[2];
		};

		Vector2();
		Vector2(float _x, float _y);
		Vector2(const Vector3& vector);
		Vector2 operator*(float scalar);
		Vector2 operator+(float scalar);

		Vector2& operator+=(const Vector2& other);
		Vector2 operator+(const Vector2& other);
		Vector2 operator-(const Vector2& other);
		Vector2 operator-();
		Vector2& operator=(const Vector3& vector);

		Vector2 Normalize();
		float Dot(Vector2& other);
		float Length();

		static Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max);
	};
}



