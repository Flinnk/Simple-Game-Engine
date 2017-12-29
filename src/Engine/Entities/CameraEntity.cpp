#include <Engine\Entities\CameraEntity.h>
#include <Engine\Entities\EntityFactory.h>

namespace GameEngine
{

	ImplementEntityFactory(CameraEntity)

	CameraEntity::CameraEntity() : Entity()
	{
		
		CameraComp = new CameraComponent();
		AddComponent(CameraComp);
	}

	CameraComponent* CameraEntity::GetCamera()
	{
		return CameraComp;
	}

	void CameraEntity::Deserialize(JSONObject& Data)
	{
		if (Data.find(L"CameraComp") != Data.end() && Data[L"CameraComp"]->IsObject())
		{
			JSONObject cameraComp = Data[L"CameraComp"]->AsObject();
			CameraComp->Deserialize(cameraComp);
		}
	}
}
