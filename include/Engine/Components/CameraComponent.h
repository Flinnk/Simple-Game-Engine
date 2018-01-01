#pragma once

#include <Engine\Components\SceneComponent.h>
#include <Engine\Renderer\Camera.h>

namespace GameEngine
{
	class CameraComponent : public SceneComponent
	{

		DeclareComponentFactory(CameraComponent)
	public:
		virtual void OnInitialize()override;

		void SetCameraData(const Camera& Data);
		Camera GetCameraData() const;
		virtual void Deserialize(JSONObject& Data) override;

	private:
		Camera CameraData;
	};
}
