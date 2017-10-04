#include "Renderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
namespace GameEngine {

	Renderer::Renderer(Shader* SpriteShader, Shader* TextShader)
	{
		SpriteRender = new SpriteRenderer(SpriteShader);
		TextRender = new TextRenderer(TextShader);
		TextRender->Load("C:\\Windows\\Fonts\\Arial.ttf",96);
	}

	Renderer::~Renderer()
	{
		Release();
	}

	void Renderer::DrawTexture(const Texture *texture, const Vector2& position,
		const Vector2& size, float rotate,
		const Vector3& color) const
	{
		if (SpriteRender)
			SpriteRender->DrawTexture(texture, position, size, rotate, color);
	}

	void Renderer::DrawText(const std::string& text, float x, float y, float scale, const Vector3& color) const
	{
		if (TextRender)
			TextRender->DrawText(text,x,y,scale,color);
	}

	void Renderer::Release()
	{
		if (SpriteRender)
			delete SpriteRender;

		SpriteRender = nullptr;

		if (TextRender)
			delete TextRender;

		TextRender = nullptr;
	}
}
