#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

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
#endif // !CAMERA_COMPONENT_H
