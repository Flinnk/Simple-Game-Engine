#pragma once

#include <Engine\Components\SceneComponent.h>
#include <Engine\Renderer\Camera.h>

namespace GameEngine
{
	class CameraComponent : public SceneComponent
	{
	public:
		void SetCameraData(const Camera& Data);
		Camera GetCameraData();
	private:
		Camera CameraData;
	};
}
