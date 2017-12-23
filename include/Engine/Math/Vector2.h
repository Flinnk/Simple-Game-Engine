#pragma once

namespace GameEngine 
{
	struct Vector2 {
		float x, y;

		Vector2();
		Vector2(float _x, float _y);
		Vector2 operator*(float scalar);
		Vector2 operator+(float scalar);

		Vector2& operator+=(const Vector2& other);
		Vector2 operator+(const Vector2& other);
		Vector2 operator-(const Vector2& other);
		Vector2 operator-();

		Vector2 Normalize();
		float Dot(Vector2& other);
		float Length();

		static Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max);
	};
}



