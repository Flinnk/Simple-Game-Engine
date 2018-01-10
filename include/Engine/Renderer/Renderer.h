#pragma once 

#include <string>
#include <Engine\Renderer\RenderData.h>


namespace GameEngine {


	class SpriteRenderer;
	class TextRenderer;
	class Shader;

	class Texture;
	class CameraComponent;
	class SpriteComponent;
	struct Rect;

	class Renderer {
	public:

		Renderer(Shader* SpriteShader, Shader* TextShader);
		~Renderer();

		void DrawSprite(const DrawCall2D& DrawCall) const;
		void DrawText(const std::string& text, float x, float y, float scale, const Vector3& color) const;

		void End();
		void Release();

		unsigned int GetDrawCallStats();
		void ClearDebugStats();

		void ClearCameraData();

		void SetCamera(const CameraComponent* Camera);
	private:
		SpriteRenderer* SpriteRender = nullptr;
		TextRenderer* TextRender = nullptr;
		const CameraComponent* Camera = nullptr;
	};

}
