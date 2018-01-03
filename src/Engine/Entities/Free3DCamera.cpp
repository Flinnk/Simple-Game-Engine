#include <Engine\Entities\Free3DCamera.h>
#include <Engine\Entities\EntityFactory.h>
#include <Engine\Core\Input.h>
#include <Engine\Math\Math.h>

namespace GameEngine
{
	ImplementEntityFactory(Free3DCamera);

	Free3DCamera::Free3DCamera() : WorldUpVector(0, 1, 0)
	{
		CameraComp->SetRelativeRotation(Vector3(0, -90, 0));

		Input::GetMousePosition(LastMouseX, LastMouseY);
		UpdateVectors();
	}


	void Free3DCamera::Update(float DeltaSeconds)
	{
		CameraEntity::Update(DeltaSeconds);
		int X, Y;
		Input::GetMousePosition(X, Y);

		int diffX = X- LastMouseX;
		int diffY = Y- LastMouseY;

		Vector3 Rotation = CameraComp->GetRelativeRotation();
		if (Input::GetMouseButton(Mouse::RIGHT_BUTTON))
		{
			Rotation.y += diffX*DeltaSeconds*Speed;
			Rotation.x += diffY*DeltaSeconds*Speed;

			if (Rotation.x > 89.0f)
				Rotation.x = 89.0f;
			if (Rotation.x < -89.0f)
				Rotation.x = -89.0f;
		}
		Vector3 Position = CameraComp->GetRelativePosition();

		if (Input::GetKey(Keyboard::W))
		{
			Position += FrontVector * Speed * DeltaSeconds;
		}
		else if (Input::GetKey(Keyboard::A))
		{
			Position -= RightVector * Speed * DeltaSeconds;

		}
		else if (Input::GetKey(Keyboard::S))
		{
			Position -= FrontVector * Speed * DeltaSeconds;

		}
		else if (Input::GetKey(Keyboard::D))
		{
			Position += RightVector * Speed * DeltaSeconds;

		}


		CameraComp->SetRelativePosition(Position);
		CameraComp->SetRelativeRotation(Rotation);

		UpdateVectors();

		LastMouseX = X;
		LastMouseY = Y;

	}

	Matrix4 Free3DCamera::GetViewMatrix()
	{
		return Matrix4::LookAt(CameraComp->GetAbsolutePosition(), CameraComp->GetAbsolutePosition() + FrontVector, UpVector);
	}

	void Free3DCamera::UpdateVectors()
	{
		Vector3 rotation = CameraComp->GetRelativeRotation();

		Vector3 front;
		front.x = cos(ToRadians(rotation.y)) * cos(ToRadians(rotation.x));
		front.y = sin(ToRadians(rotation.x));
		front.z = sin(ToRadians(rotation.y)) * cos(ToRadians(rotation.x));
		FrontVector = front.Normalize();

		RightVector = Vector3::Cross(FrontVector, WorldUpVector).Normalize();
		UpVector = Vector3::Cross(RightVector, FrontVector).Normalize();
	}

}