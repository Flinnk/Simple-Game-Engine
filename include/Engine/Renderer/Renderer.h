#pragma once 

#include <string>

namespace GameEngine {


	class SpriteRenderer;
	class TextRenderer;
	class Shader;
	struct Vector2;
	struct Vector3;
	class Texture;
	struct Camera;
	struct Transform;

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

		void SetCameraTransform(Transform* CameraTransform);
		void SetCameraData(Camera* CameraData);
	private:
		SpriteRenderer* SpriteRender = nullptr;
		TextRenderer* TextRender = nullptr;
		Transform* CameraTransform = nullptr;
		Camera* CameraData = nullptr;
	};

}
