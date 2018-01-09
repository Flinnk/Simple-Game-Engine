#pragma once

#include <Engine\Components\SceneComponent.h>
#include <Engine\Graphics\TextureAtlas.h>
#include <map>

namespace GameEngine
{
	class Texture;
	class Renderer;
	struct Vector3;
	struct Rect;

	struct AnimationClip {
		AnimationClip(){}
		int InitialTextureRegion=0;
		int FinalTextureRegion=0;
		float FramesPerSecond=60.0f;
	};

	class SpriteComponent : public SceneComponent
	{
		DeclareComponentFactory(SpriteComponent)
	public:
		SpriteComponent();
		virtual void Deserialize(JSONObject& Data) override;
		virtual void Update(float DeltaSeconds)override;
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
		int  GetCurrentDrawingRegionIndex()const;

		void AddAnimationClip(const char* Name,const AnimationClip& Clip);
		void PlayAnimation(const char* ClipName);
		void StopCurrentAnimation();
	private:
		std::map<std::string, AnimationClip> Animations;
		float CurrentAnimationPlayTime = 0.0f;
		const AnimationClip* CurrentAnimation = nullptr;

		const TextureAtlas* SpriteAtlas = nullptr;
		Vector3 TintColor;
		unsigned int OrderInLayer = 0;
		int CurrentDrawingRegionIndex = 0;

	};
}