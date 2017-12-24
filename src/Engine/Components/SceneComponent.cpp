#include <Engine\Components\SceneComponent.h>
#include <Engine\Core\Entity.h>
namespace GameEngine
{

	Transform SceneComponent::GetTransform() const
	{
		return ComponentTransform;
	}

	void SceneComponent::SetTransform(const Transform& Value)
	{
		ComponentTransform = Value;
	}


	Vector3 SceneComponent::GetAbsolutePosition() const
	{
		Entity* ComponentOwner = GetOwner();
		if (ComponentOwner)
		{
			return (ComponentOwner->GetAbsolutePosition() + ComponentTransform.Position);
		}
		else
		{
			return ComponentTransform.Position;
		}
	}

	Vector3 SceneComponent::GetRelativePosition() const
	{
		return ComponentTransform.Position;
	}


	void SceneComponent::SetRelativePosition(const Vector3& Value)
	{
		ComponentTransform.Position = Value;
	}

	Vector3 SceneComponent::GetAbsoluteRotation() const
	{
		Entity* ComponentOwner = GetOwner();
		if (ComponentOwner)
		{
			return (ComponentOwner->GetAbsoluteRotation() + ComponentTransform.Rotation);
		}
		else
		{
			return ComponentTransform.Rotation;
		}
	}

	Vector3 SceneComponent::GetRelativeRotation() const
	{
		return ComponentTransform.Rotation;
	}

	void SceneComponent::SetRelativeRotation(const Vector3& Value)
	{
		ComponentTransform.Rotation = Value;
	}

	Vector3 SceneComponent::GetAbsoluteScale() const
	{
		Entity* ComponentOwner = GetOwner();
		if (ComponentOwner)
		{
			return (ComponentOwner->GetAbsoluteScale() + ComponentTransform.Scale);
		}
		else
		{
			return ComponentTransform.Scale;
		}
	}

	Vector3 SceneComponent::GetRelativeScale() const 
	{
		return ComponentTransform.Scale;
	}

	void SceneComponent::SetRelativeScale(const Vector3& Value)
	{
		ComponentTransform.Scale = Value;
	}
}