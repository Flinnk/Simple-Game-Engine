#pragma once

#include <Engine\Components\SceneComponent.h>
#include <Engine\Graphics\TextureAtlas.h>

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

		const Texture* GetTexture()const;
		const TextureAtlas* GetTextureAtlas() const;
		void SetTextureAtlas(const TextureAtlas* Atlas);

		int GetRenderIdentifier() const;
		Vector3 GetTintColor() const;
		void SetTintColor(const Vector3& Color);
		Rect GetBounds() const;
		unsigned int GetOrderInLayer()const;
		void SetOrderInLayer(unsigned int Order);

		const TextureRegion& GetCurrentRegion()const;
		void SetCurrentDrawingRegionIndex(int index);
		int  GetCurrentDrawingRegionIndex()const ;

	private:
		const TextureAtlas* SpriteAtlas = nullptr;
		Vector3 TintColor;
		unsigned int OrderInLayer = 0;
		int CurrentDrawingRegionIndex = 0;
	};
}