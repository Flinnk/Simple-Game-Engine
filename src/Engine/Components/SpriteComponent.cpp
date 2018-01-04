#include <Engine\Components\SpriteComponent.h>
#include <Engine\Components\ComponentFactory.h>
#include <Engine\Utils\ResourceManager.h>
#include <Engine\Renderer\Renderer.h>
#include <Engine\Math\Vector2.h>

namespace GameEngine
{
	ImplementComponentFactory(SpriteComponent)

	SpriteComponent::SpriteComponent() : TintColor(Vector3(1,1,1)){}

	void SpriteComponent::Deserialize(JSONObject& Data)
	{
		SceneComponent::Deserialize(Data);

		if (Data.find(L"SpriteTexture") != Data.end() && Data[L"SpriteTexture"]->IsString())
		{
			ResourceManager& resManager = ResourceManager::GetInstance();
			const std::wstring& rawPath = Data[L"SpriteTexture"]->AsString();
			std::string texturePath = std::string(rawPath.begin(), rawPath.end());
			SpriteTexture = resManager.LoadTexture(texturePath.c_str());
		}
	}

	void SpriteComponent::SetTexture(const Texture* Texture)
	{
		SpriteTexture = Texture;
	}

	const Texture* SpriteComponent::GetTexture() const
	{
		return SpriteTexture;
	}

	void SpriteComponent::Render(class GameEngine::Renderer* Renderer)
	{
		if (SpriteTexture)
		{
			Vector2 position = GetAbsolutePosition();
			Vector3 size = GetAbsoluteScale();
			size.x *= SpriteTexture->GetWidth();
			size.y *= SpriteTexture->GetHeight();

			Vector3 rotation = GetAbsoluteRotation();
			Renderer->DrawSprite(this);
		}
	}

	int SpriteComponent::GetRenderIdentifier() const
	{
		if (SpriteTexture)
			return SpriteTexture->GetID();
		return 0;
	}

	Vector3 SpriteComponent::GetTintColor() const
	{
		return TintColor;
	}

	void SpriteComponent::SetTintColor(const Vector3& Color)
	{
		TintColor = Color;
	}


}