#pragma once 

#include <string>

namespace GameEngine {


	class SpriteRenderer;
	class TextRenderer;
	class Shader;
	struct Vector2;
	struct Vector3;
	class Texture;
	class CameraComponent;

	class Renderer {
	public:

		Renderer(Shader* SpriteShader, Shader* TextShader);
		~Renderer();

		void DrawTexture(const Texture *texture, const Vector2& position,
			const Vector2& size, float rotate,
			const Vector3& color) const;
		void DrawText(const std::string& text, float x, float y, float scale, const Vector3& color) const;

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
