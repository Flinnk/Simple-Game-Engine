#pragma once 

#include <Engine\Entities\CameraEntity.h>

namespace GameEngine
{
	struct Vector3;
	struct Matrix4;
	class Free3DCamera : public CameraEntity
	{
		DeclareEntityFactory(Free3DCamera)

	public:
		Free3DCamera();
		virtual void Update(float DeltaSeconds) override ;
		Matrix4 GetViewMatrix();
	private:
		void UpdateVectors();

		float Speed = 5.0f;
		Vector3 FrontVector;
		Vector3 RightVector;
		Vector3 UpVector;
		Vector3 WorldUpVector;

		int LastMouseX, LastMouseY;
	};
}