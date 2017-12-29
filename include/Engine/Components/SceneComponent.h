#pragma once 

#include <Engine\Core\Component.h>
#include <Engine\Core\Transform.h>

namespace GameEngine
{
	class SceneComponent : public Component
	{

		RegisterComponentFactory(SceneComponent)
	public:

		virtual void Deserialize(JSONObject& Data) override;
		Transform GetTransform() const;
		void SetTransform(const Transform& Value);

		Vector3 GetAbsolutePosition() const;
		Vector3 GetRelativePosition() const;
		void SetRelativePosition(const Vector3& Value);

		Vector3 GetAbsoluteRotation() const;
		Vector3 GetRelativeRotation() const;
		void SetRelativeRotation(const Vector3& Value);

		Vector3 GetAbsoluteScale() const;
		Vector3 GetRelativeScale() const;
		void SetRelativeScale(const Vector3& Value);
	private:
		Transform ComponentTransform;
	};
}


