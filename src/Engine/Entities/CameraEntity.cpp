#include <Engine\Entities\CameraEntity.h>

namespace GameEngine
{
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
