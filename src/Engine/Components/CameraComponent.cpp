#include <Engine\Components\CameraComponent.h>
#include <Engine\Components\ComponentFactory.h>
#include <Engine\Core\Entity.h>
#include <Engine\Core\Scene.h>
namespace GameEngine
{
	ImplementComponentFactory(CameraComponent)

		void CameraComponent::SetCameraData(const Camera& Data)
	{
		CameraData = Data;
	}

	Camera CameraComponent::GetCameraData() const
	{
		return CameraData;
	}

	void CameraComponent::OnInitialize()
	{
		SceneComponent::OnInitialize();
		if (GetOwner())
		{
			Scene* scene = GetOwner()->GetScene();
			if (scene && scene->GetCamera()==nullptr)
			{
				scene->SetCamera(this);
			}
		}
	}


	void CameraComponent::Deserialize(JSONObject& Data)
	{
		SceneComponent::Deserialize(Data);
		if (Data.find(L"Camera") != Data.end() && Data[L"Camera"]->IsObject())
		{
			JSONObject camera = Data[L"Camera"]->AsObject();

			if (camera.find(L"FieldOfView") != camera.end() && camera[L"FieldOfView"]->IsNumber())
				CameraData.FieldOfView = camera[L"FieldOfView"]->AsNumber();

			if (camera.find(L"NearPlane") != camera.end() && camera[L"NearPlane"]->IsNumber())
				CameraData.NearPlane = camera[L"NearPlane"]->AsNumber();

			if (camera.find(L"FarPlane") != camera.end() && camera[L"FarPlane"]->IsNumber())
				CameraData.FarPlane = camera[L"FarPlane"]->AsNumber();

			if (camera.find(L"Mode") != camera.end() && camera[L"Mode"]->IsNumber())
				CameraData.Mode = static_cast<CameraMode>(static_cast<unsigned char>(camera[L"Mode"]->AsNumber()));

		}
	}

}