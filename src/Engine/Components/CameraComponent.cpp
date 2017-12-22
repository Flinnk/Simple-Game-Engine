#include <Engine\Components\CameraComponent.h>

namespace GameEngine
{
	void CameraComponent::SetCameraData(const Camera& Data)
	{
		CameraData = Data;
	}

	Camera CameraComponent::GetCameraData()
	{
		return CameraData;
	}
}