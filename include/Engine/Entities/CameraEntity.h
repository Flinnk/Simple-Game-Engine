#pragma once

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
