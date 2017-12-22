#include <Engine\Renderer\Renderer.h>
#include <Engine\Renderer\SpriteRenderer.h>
#include <Engine\Renderer\TextRenderer.h>

namespace GameEngine {

	Renderer::Renderer(Shader* SpriteShader, Shader* TextShader)
	{
		SpriteRender = new SpriteRenderer(SpriteShader);
		TextRender = new TextRenderer(TextShader);
		TextRender->Load("C:\\Windows\\Fonts\\Arial.ttf", 96);
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
			SpriteRender->DrawTexture(CameraTransform, CameraData, texture, position, size, rotate, color);
	}

	void Renderer::DrawText(const std::string& text, float x, float y, float scale, const Vector3& color) const
	{
		if (TextRender)
			TextRender->DrawText(CameraTransform, CameraData, text, x, y, scale, color);
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

	unsigned int Renderer::GetDrawCallStats()
	{
		return SpriteRender->GetDrawCallStats() + TextRender->GetDrawCallStats();
	}

	void Renderer::ClearDebugStats()
	{
		SpriteRender->ResetStats();
		TextRender->ResetStats();
	}

	void Renderer::ClearCameraData()
	{
		CameraTransform = nullptr;
		CameraData = nullptr;
	}

	void Renderer::SetCameraTransform(Transform* Transform)
	{
		CameraTransform = Transform;
	}

	void Renderer::SetCameraData(Camera* Data)
	{
		CameraData = Data;
	}


}
