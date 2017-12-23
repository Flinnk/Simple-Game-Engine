#pragma once 

#include <Engine\Core\Component.h>
#include <Engine\Core\Transform.h>

namespace GameEngine
{
	class SceneComponent : public Component
	{
	public:

		Transform GetTransform();
		void SetTransform(const Transform& Value);

		Vector3 GetAbsolutePosition();
		Vector3 GetRelativePosition();
		void SetRelativePosition(const Vector3& Value);

		Vector3 GetAbsoluteRotation();
		Vector3 GetRelativeRotation();
		void SetRelativeRotation(const Vector3& Value);

		Vector3 GetAbsoluteScale();
		Vector3 GetRelativeScale();
		void SetRelativeScale(const Vector3& Value);
	private:
		Transform ComponentTransform;
	};
}


