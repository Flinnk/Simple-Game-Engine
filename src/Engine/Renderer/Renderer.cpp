#include <Engine\Renderer\Renderer.h>
#include <Engine\Renderer\SpriteRenderer.h>
#include <Engine\Renderer\TextRenderer.h>
#include <Engine\Math\Vector3.h>
#include <Engine\Components\CameraComponent.h>
#include <Engine\Core\Engine.h>
#include <Engine\Graphics\OpenGL.h>
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

	void Renderer::DrawSprite(const DrawCall2D& DrawCall) const
	{
		if (SpriteRender)
			SpriteRender->Submit(DrawCall);
	}

	void Renderer::DrawText(const std::string& text, float x, float y, float scale, const Vector3& color) const
	{
		if (TextRender)
		{
			//Once the TextRenderer is integrated with the SpriteRenderer in a batch 2D renderer this will be called once in the End function
			//As we have to combine the render with the render of 3d geometry and we have to enable depth test, in 2D this will interfere with blending and drawing
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			TextRender->DrawText(Camera, text, x, y, scale, color);
			glDisable(GL_BLEND);
		}
	}

	void Renderer::End()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		SpriteRender->Draw();
		glDisable(GL_BLEND);

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
		Camera = nullptr;
	}


	void Renderer::SetCamera(const CameraComponent* CameraPointer)
	{
		Camera = CameraPointer;
		SpriteRender->SetCamera(CameraPointer);
	}


}
