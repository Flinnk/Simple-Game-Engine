#ifndef CAMERA_ENTITY_H
#define CAMERA_ENTITY_H

#include <Engine\Core\Entity.h>
#include <Engine\Components\CameraComponent.h>
namespace GameEngine
{
	class CameraEntity : public Entity
	{

	public:
		CameraEntity();
		CameraComponent* GetCamera();
	private:
		CameraComponent* Camera;
	};
}
#endif // !CAMERA_ENTITY_H
