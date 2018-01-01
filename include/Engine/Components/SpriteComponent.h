#pragma once

#include <Engine\Components\SceneComponent.h>

namespace GameEngine
{
	class Texture;
	class Renderer;
	struct Vector3;

	class SpriteComponent : public SceneComponent
	{
		DeclareComponentFactory(SpriteComponent)
	public:
		SpriteComponent();
		virtual void Deserialize(JSONObject& Data) override;
		virtual void Render(class GameEngine::Renderer* Renderer);

		void SetTexture(const Texture* Texture);
		const Texture* GetTexture();
	private:
		const Texture* SpriteTexture = nullptr;
		Vector3 TintColor;
	};
}