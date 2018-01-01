#include <Engine\Components\SceneComponent.h>
#include <Engine\Core\Entity.h>
#include <Engine\Components\ComponentFactory.h>
namespace GameEngine
{
	ImplementComponentFactory(SceneComponent)

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
			return (ComponentOwner->GetAbsoluteScale() * ComponentTransform.Scale);
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

	void SceneComponent::Deserialize(JSONObject& Data)
	{
		if (Data.find(L"Transform") != Data.end() && Data[L"Transform"]->IsObject()) {
			JSONObject transform = Data[L"Transform"]->AsObject();
			if (transform.find(L"Position") != transform.end() && transform[L"Position"]->IsArray())
			{
				JSONArray position = transform[L"Position"]->AsArray();
				Vector3 deserializePosition;
				for (int i = 0; i < 3; ++i) {
					deserializePosition.elements[i] = position[i]->AsNumber();
				}
				SetRelativePosition(deserializePosition);
			}

			if (transform.find(L"Rotation") != transform.end() && transform[L"Rotation"]->IsArray())
			{
				JSONArray rotation = transform[L"Rotation"]->AsArray();
				Vector3 deserializeRotation;
				for (int i = 0; i < 3; ++i) {
					deserializeRotation.elements[i] = rotation[i]->AsNumber();
				}
				SetRelativeRotation(deserializeRotation);
			}

			if (transform.find(L"Scale") != transform.end() && transform[L"Scale"]->IsArray())
			{
				JSONArray scale = transform[L"Scale"]->AsArray();
				Vector3 deserializeScale;
				for (int i = 0; i < 3; ++i) {
					deserializeScale.elements[i] = scale[i]->AsNumber();
				}
				SetRelativeScale(deserializeScale);
			}
		}
	}

}