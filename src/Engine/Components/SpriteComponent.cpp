#include <Engine\Components\SpriteComponent.h>
#include <Engine\Components\ComponentFactory.h>
#include <Engine\Utils\ResourceManager.h>
#include <Engine\Renderer\Renderer.h>
#include <Engine\Math\Vector2.h>
#include <Engine\Math\Rect.h>

namespace GameEngine
{
	ImplementComponentFactory(SpriteComponent)

		SpriteComponent::SpriteComponent() : TintColor(Vector3(1, 1, 1))
	{
		RenderingRequire = true;
		UpdateRequire = true;
	}

	void SpriteComponent::Deserialize(JSONObject& Data)
	{
		SceneComponent::Deserialize(Data);

		if (Data.find(L"SpriteTexture") != Data.end() && Data[L"SpriteTexture"]->IsString())
		{
			ResourceManager& resManager = ResourceManager::GetInstance();
			const std::wstring& rawPath = Data[L"SpriteTexture"]->AsString();
			std::string texturePath = std::string(rawPath.begin(), rawPath.end());
			SpriteAtlas = resManager.LoadTextureAtlas(texturePath.c_str());
		}
	}

	void SpriteComponent::Update(float DeltaSeconds)
	{
		if (CurrentAnimation)
		{
			CurrentAnimationPlayTime += DeltaSeconds;
			if (CurrentAnimationPlayTime > (1 / CurrentAnimation->FramesPerSecond))
			{
				CurrentAnimationPlayTime = 0;
				++CurrentDrawingRegionIndex;
				if (CurrentDrawingRegionIndex > CurrentAnimation->FinalTextureRegion)
					CurrentDrawingRegionIndex = CurrentAnimation->InitialTextureRegion;
			}
		}
	}

	void SpriteComponent::Render(class GameEngine::Renderer* Renderer)
	{
		if (SpriteAtlas && SpriteAtlas->GetTexture())
		{
			Vector2 position = GetAbsolutePosition();
			Vector3 size = GetAbsoluteScale();
			size.x *= SpriteAtlas->GetTexture()->GetWidth();
			size.y *= SpriteAtlas->GetTexture()->GetHeight();

			Vector3 rotation = GetAbsoluteRotation();
			Renderer->DrawSprite(this);
		}
	}

	const TextureAtlas* SpriteComponent::GetTextureAtlas() const
	{
		return SpriteAtlas;
	}

	void SpriteComponent::SetTextureAtlas(const TextureAtlas* Atlas)
	{
		SpriteAtlas = Atlas;
	}

	const Texture* SpriteComponent::GetTexture()const
	{
		if (SpriteAtlas)
			return SpriteAtlas->GetTexture();
		return nullptr;
	}


	int SpriteComponent::GetRenderIdentifier() const
	{
		int identifier = 0;
		identifier = (OrderInLayer << 24) | (GetTexture()->GetID() << 8);

		return identifier;
	}

	Vector3 SpriteComponent::GetTintColor() const
	{
		return TintColor;
	}

	void SpriteComponent::SetTintColor(const Vector3& Color)
	{
		TintColor = Color;
	}

	Rect SpriteComponent::GetBounds() const
	{
		Vector3 position = GetAbsolutePosition();
		Vector3 size = GetAbsoluteScale();
		size.x *= GetTexture()->GetWidth();
		size.y *= GetTexture()->GetHeight();

		return { position.x ,position.y,size.x,size.y };
	}

	unsigned int SpriteComponent::GetOrderInLayer() const
	{
		return OrderInLayer;
	}

	void SpriteComponent::SetOrderInLayer(unsigned int Order)
	{
		OrderInLayer = Order;
	}

	const TextureRegion& SpriteComponent::GetCurrentRegion()const
	{
		return SpriteAtlas ? SpriteAtlas->GetTextureRegion(CurrentDrawingRegionIndex) : TextureRegion();
	}

	void SpriteComponent::SetCurrentDrawingRegionIndex(int index)
	{
		CurrentDrawingRegionIndex = std::fmaxf(0, std::fminf(SpriteAtlas->RegionsNum(), index));//Clamp
	}

	int  SpriteComponent::GetCurrentDrawingRegionIndex()const
	{
		return CurrentDrawingRegionIndex;
	}

	void SpriteComponent::AddAnimationClip(const char* Name, const AnimationClip& Clip)
	{
		std::string name(Name);
		if (Animations.find(name) == Animations.end())
		{
			Animations[name] = Clip;
		}
	}

	void SpriteComponent::PlayAnimation(const char* ClipName)
	{
		std::string name(ClipName);
		if (Animations.find(name) != Animations.end())
		{
			if (&Animations[name] != CurrentAnimation)
			{
				StopCurrentAnimation();
				CurrentAnimation = &Animations[name];
				CurrentDrawingRegionIndex = CurrentAnimation->InitialTextureRegion;
			}
		}
		else 
		{
			StopCurrentAnimation();
		}
	}

	void SpriteComponent::StopCurrentAnimation()
	{
		CurrentAnimation = nullptr;
		CurrentAnimationPlayTime = 0;
	}


}