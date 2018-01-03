#include  <Engine\Math\Vector3.h>
#include  <Engine\Math\Vector2.h>
#include <math.h>
namespace GameEngine
{

	Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	Vector3::Vector3(const Vector2& vector) : x(vector.x), y(vector.y) {}

	Vector3 Vector3::operator*(float scalar) const
	{
		return Vector3(x*scalar, y*scalar, z*scalar);
	}

	Vector3 Vector3::operator+(const Vector3& rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}


	Vector3 Vector3::operator*(const Vector3& rhs) const
	{
		return Vector3(x*rhs.x, y*rhs.y, z*rhs.z);
	}

	Vector3& Vector3::operator=(const Vector2& vector)
	{
		x = vector.x;
		y = vector.y;
		return *this;
	}

	Vector3 Vector3::Normalize()
	{
		Vector3 NormalizedVector(0, 0, 0);
		float VectorLength = Length();

		NormalizedVector.x = x / VectorLength;
		NormalizedVector.y = y / VectorLength;
		NormalizedVector.z = z / VectorLength;

		return NormalizedVector;
	}

	float Vector3::Length()
	{
		return static_cast<float>(sqrt((x*x) + (y*y) + (z*z)));
	}

	Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 Result;

		Result.x = (lhs.y*rhs.z) - (lhs.z*rhs.y);
		Result.y = (lhs.z*rhs.x) - (lhs.x*rhs.z);
		Result.z = (lhs.x*rhs.y) - (lhs.y*rhs.x);

		return Result;
	}

	float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 temp = lhs*rhs;
		return temp.x + temp.y + temp.z;
	}


	Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

}