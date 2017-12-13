#include  <Engine\Math\Utils.h>
#include  <Engine\Math\Vector2.h>

namespace GameEngine
{

	Vector2::Vector2() : x(0.0f), y(0.0f) {}
	Vector2::Vector2(float _x, float _y) : x(_x), y(_y) {}

	Vector2 Vector2::operator-()
	{
		return Vector2(-x, -y);
	}

	Vector2 Vector2::operator*(float scalar)
	{
		return Vector2(x*scalar, y*scalar);
	}

	Vector2 Vector2::operator+(float scalar)
	{
		return Vector2(x + scalar, y + scalar);

	}


	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}


	Vector2 Vector2::operator+(const Vector2& other)
	{
		Vector2 Result;

		Result.x = x + other.x;
		Result.y = y + other.y;

		return Result;
	}


	Vector2 Vector2::operator-(const Vector2& other)
	{
		Vector2 Result;

		Result.x = x - other.x;
		Result.y = y - other.y;

		return Result;
	}

	Vector2 Vector2::Normalize()
	{
		Vector2 NormalizedVector (0,0);
		float VectorLength = Length();

		NormalizedVector.x = x / VectorLength;
		NormalizedVector.y = y / VectorLength;

		return NormalizedVector;
	}

	float Vector2::Dot(Vector2& other)
	{
		return ((x*other.x) + (y*other.y));
	}

	float Vector2::Length()
	{
		return static_cast<float>(sqrt((x*x) + (y*y)));
	}


	Vector2 Vector2::Clamp(Vector2 value, Vector2 min, Vector2 max)
	{
		Vector2 Result;

		Result.x = ClampFloat(value.x, min.x, max.x);
		Result.y = ClampFloat(value.y, min.y, max.y);

		return Result;
	}

}