#include <Engine\Components\SpriteComponent.h>
#include <Engine\Components\ComponentFactory.h>
#include <Engine\Utils\ResourceManager.h>
#include <Engine\Renderer\Renderer.h>
#include <Engine\Math\Vector2.h>
#include <Engine\Math\Rect.h>

namespace GameEngine
{
	ImplementComponentFactory(SpriteComponent)

	SpriteComponent::SpriteComponent() : TintColor(Vector3(1,1,1))
	{
		RenderingRequire = true;
	}

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
		
		return { position.x ,position.y,size.x,size.y};
	}

	unsigned int SpriteComponent::GetOrderInLayer() const 
	{
		return OrderInLayer;
	}

	void SpriteComponent::SetOrderInLayer(unsigned int Order)
	{
		OrderInLayer = Order;
	}
}