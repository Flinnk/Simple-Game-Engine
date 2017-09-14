#include "Matrix4.h"
#include "Utils.h"
#include "Vector2.h"
#include "Vector3.h"

namespace GameEngine
{

	Matrix4::Matrix4(float e0, float e4, float e8, float e12,
		float e1, float e5, float e9, float e13,
		float e2, float e6, float e10, float e14,
		float e3, float e7, float e11, float e15)
	{
		elements[0] = e0;
		elements[1] = e1;
		elements[2] = e2;
		elements[3] = e3;
		elements[4] = e4;
		elements[5] = e5;
		elements[6] = e6;
		elements[7] = e7;
		elements[8] = e8;
		elements[9] = e9;
		elements[10] = e10;
		elements[11] = e11;
		elements[12] = e12;
		elements[13] = e13;
		elements[14] = e14;
		elements[15] = e15;

	}

	Matrix4::Matrix4()
	{
		for (int i = 0; i < 4 * 4; ++i) {
			elements[i] = 0;
		}
	}

	Matrix4::Matrix4(float Diagonal)
	{
		for (int i = 0; i < 4 * 4; ++i) {
			elements[i] = 0;
		}

		elements[0] = Diagonal;
		elements[5] = Diagonal;
		elements[10] = Diagonal;
		elements[15] = Diagonal;

	}

	Matrix4 Matrix4::Identity()
	{
		return Matrix4(1.0f);
	}


	Matrix4 Matrix4::Scale(const Vector3& ScaleVector)
	{
		Matrix4 Result(1.0f);

		Result.elements[0] = ScaleVector.x;
		Result.elements[5] = ScaleVector.y;
		Result.elements[10] = ScaleVector.z;

		return Result;
	}

	Matrix4 Matrix4::Scale(const Vector2& ScaleVector)
	{
		Matrix4 Result(1.0f);

		Result.elements[0] = ScaleVector.x;
		Result.elements[5] = ScaleVector.y;
		Result.elements[10] = 0.0f;

		return Result;
	}

	Matrix4 Matrix4::Translation(const Vector3& TranslationVector)
	{
		Matrix4 result(1.0f);

		result.elements[12] = TranslationVector.x;
		result.elements[13] = TranslationVector.y;
		result.elements[14] = TranslationVector.z;


		return result;
	}

	Matrix4 Matrix4::Translation(const Vector2& TranslationVector)
	{
		Matrix4 result(1.0f);

		result.elements[12] = TranslationVector.x;
		result.elements[13] = TranslationVector.y;
		result.elements[14] = 0.0f;

		return result;
	}


	Matrix4 Matrix4::Rotation(float Angle, const Vector3& Axis)
	{
		Matrix4 Result(1.0f);

		float Radians = ToRadians(Angle);

		float Cos = cos(Radians);
		float Sin = sin(Radians);
		float OMC = 1.0 - Cos;//One Minus Cosine

		Result.elements[0] = Cos + Axis.x*Axis.x*OMC;
		Result.elements[1] = Axis.y*Axis.x*OMC + Axis.z*Sin;
		Result.elements[2] = Axis.z*Axis.x*OMC - Axis.y*Sin;

		Result.elements[4] = Axis.x*Axis.y*OMC - Axis.z*Sin;
		Result.elements[5] = Cos + Axis.y*Axis.y*OMC;
		Result.elements[6] = Axis.z*Axis.y*OMC + Axis.x*Sin;

		Result.elements[8] = Axis.x*Axis.z*OMC + Axis.y*Sin;
		Result.elements[9] = Axis.y*Axis.z*OMC - Axis.x*Sin;
		Result.elements[10] = Cos + Axis.z*Axis.z*OMC;

		return Result;
	}

	Matrix4 Matrix4::Ortho(float Left, float Right, float Bottom, float Top, float NearPlane, float FarPlane)
	{
		Matrix4 Result(1.0f);

		Result.elements[0] = 2 / (Right - Left);
		Result.elements[5] = 2 / (Top - Bottom);
		Result.elements[10] = -2 / (FarPlane - NearPlane);

		Result.elements[12] = -(Right + Left) / (Right - Left);
		Result.elements[13] = -(Top + Bottom) / (Top - Bottom);
		Result.elements[14] = -(FarPlane + NearPlane) / (FarPlane - NearPlane);
		return Result;
	}


	Matrix4 Matrix4::Multiply(const Matrix4& Left, const Matrix4& Right)
	{
		Matrix4 result(1.0f);

		result.elements[0] = Right.elements[0] * Left.elements[0] + Right.elements[1] * Left.elements[4] + Right.elements[2] * Left.elements[8] + Right.elements[3] * Left.elements[12];
		result.elements[1] = Right.elements[0] * Left.elements[1] + Right.elements[1] * Left.elements[5] + Right.elements[2] * Left.elements[9] + Right.elements[3] * Left.elements[13];
		result.elements[2] = Right.elements[0] * Left.elements[2] + Right.elements[1] * Left.elements[6] + Right.elements[2] * Left.elements[10] + Right.elements[3] * Left.elements[14];
		result.elements[3] = Right.elements[0] * Left.elements[3] + Right.elements[1] * Left.elements[7] + Right.elements[2] * Left.elements[11] + Right.elements[3] * Left.elements[15];
		result.elements[4] = Right.elements[4] * Left.elements[0] + Right.elements[5] * Left.elements[4] + Right.elements[6] * Left.elements[8] + Right.elements[7] * Left.elements[12];
		result.elements[5] = Right.elements[4] * Left.elements[1] + Right.elements[5] * Left.elements[5] + Right.elements[6] * Left.elements[9] + Right.elements[7] * Left.elements[13];
		result.elements[6] = Right.elements[4] * Left.elements[2] + Right.elements[5] * Left.elements[6] + Right.elements[6] * Left.elements[10] + Right.elements[7] * Left.elements[14];
		result.elements[7] = Right.elements[4] * Left.elements[3] + Right.elements[5] * Left.elements[7] + Right.elements[6] * Left.elements[11] + Right.elements[7] * Left.elements[15];
		result.elements[8] = Right.elements[8] * Left.elements[0] + Right.elements[9] * Left.elements[4] + Right.elements[10] * Left.elements[8] + Right.elements[11] * Left.elements[12];
		result.elements[9] = Right.elements[8] * Left.elements[1] + Right.elements[9] * Left.elements[5] + Right.elements[10] * Left.elements[9] + Right.elements[11] * Left.elements[13];
		result.elements[10] = Right.elements[8] * Left.elements[2] + Right.elements[9] * Left.elements[6] + Right.elements[10] * Left.elements[10] + Right.elements[11] * Left.elements[14];
		result.elements[11] = Right.elements[8] * Left.elements[3] + Right.elements[9] * Left.elements[7] + Right.elements[10] * Left.elements[11] + Right.elements[11] * Left.elements[15];
		result.elements[12] = Right.elements[12] * Left.elements[0] + Right.elements[13] * Left.elements[4] + Right.elements[14] * Left.elements[8] + Right.elements[15] * Left.elements[12];
		result.elements[13] = Right.elements[12] * Left.elements[1] + Right.elements[13] * Left.elements[5] + Right.elements[14] * Left.elements[9] + Right.elements[15] * Left.elements[13];
		result.elements[14] = Right.elements[12] * Left.elements[2] + Right.elements[13] * Left.elements[6] + Right.elements[14] * Left.elements[10] + Right.elements[15] * Left.elements[14];
		result.elements[15] = Right.elements[12] * Left.elements[3] + Right.elements[13] * Left.elements[7] + Right.elements[14] * Left.elements[11] + Right.elements[15] * Left.elements[15];


		return result;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& Right)
	{
		*this = Multiply(*this, Right);

		return *this;
	}


	Matrix4& Matrix4::operator*(const Matrix4& Right)
	{
		return Multiply(*this, Right);
	}
}