#pragma once

#include <Engine\Components\SceneComponent.h>

namespace GameEngine
{
	class Texture;
	class Renderer;
	struct Vector3;
	struct Rect;

	class SpriteComponent : public SceneComponent
	{
		DeclareComponentFactory(SpriteComponent)
	public:
		SpriteComponent();
		virtual void Deserialize(JSONObject& Data) override;
		virtual void Render(class GameEngine::Renderer* Renderer);

		void SetTexture(const Texture* Texture);
		const Texture* GetTexture()const ;

		int GetRenderIdentifier() const;
		Vector3 GetTintColor() const;
		void SetTintColor(const Vector3& Color);
		Rect GetBounds() const;
	private:
		const Texture* SpriteTexture = nullptr;
		Vector3 TintColor;
	};
}