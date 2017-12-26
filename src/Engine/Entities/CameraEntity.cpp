#include <Engine\Entities\CameraEntity.h>
#include <Engine\Entities\EntityFactory.h>

namespace GameEngine
{

	RegisterFactory(CameraEntity)

	CameraEntity::CameraEntity() : Entity()
	{
		
		Camera = new CameraComponent();
		AddComponent(Camera);
	}

	CameraComponent* CameraEntity::GetCamera()
	{
		return Camera;
	}
}
