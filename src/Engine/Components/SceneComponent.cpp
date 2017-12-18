#include <Engine\Components\SceneComponent.h>
#include <Engine\Core\Entity.h>
namespace GameEngine
{
	Transform& SceneComponent::GetTransform()
	{
		return ComponentTransform;
	}

	Vector3 SceneComponent::GetAbsolutePosition()
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

	Vector3 SceneComponent::GetRelativePosition()
	{
		return ComponentTransform.Position;
	}
}