#pragma once

#include <Engine\Core\Entity.h>
#include <Engine\Components\CameraComponent.h>
namespace GameEngine
{
	class CameraEntity : public Entity
	{

	public:
		virtual void Deserialize(JSONObject& Data)override;

		CameraEntity();
		CameraComponent* GetCamera();
	private:
		CameraComponent* CameraComp;
	};
}
