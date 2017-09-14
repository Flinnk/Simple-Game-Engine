#ifndef MAT4_H
#define MAT4_H

namespace GameEngine
{
	struct Matrix4 {

		float elements[4 * 4];

		Matrix4();
		Matrix4(float e0, float e4, float e8, float e12,
			float e1, float e5, float e9, float e13,
			float e2, float e6, float e10, float e14,
			float e3, float e7, float e11, float e15);
		Matrix4(float Diagonal);

		Matrix4& operator*(const Matrix4& Right);
		Matrix4& operator*=(const Matrix4& Right);

		static Matrix4 Multiply(const Matrix4& Left, const Matrix4& Right);
		static Matrix4 Identity();

		static Matrix4 Ortho(float Left, float Right, float Bottom, float Top, float NearPlane, float FarPlane);

		static Matrix4 Translation(const struct Vector3& TranslationVector);
		static Matrix4 Translation(const struct Vector2& TranslationVector);

		static Matrix4 Rotation(float Angle, const struct Vector3& Axis);

		static Matrix4 Scale(const struct Vector2& ScaleVector);
		static Matrix4 Scale(const struct Vector3& ScaleVector);

	};
}

#endif // !MAT4_H
