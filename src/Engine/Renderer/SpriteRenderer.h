#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

namespace GameEngine {

	class Shader;
	class Texture;
	struct Vector2;
	struct Vector3;
	struct Transform;
	struct Camera;

	class SpriteRenderer {
	public:
		SpriteRenderer(Shader *renderShader);
		~SpriteRenderer();

		void DrawTexture(const Transform* CameraTransform, const Camera* CameraData, const Texture *texture, Vector2 position,
			Vector2 size, float rotate,
			Vector3 color);

		unsigned int GetDrawCallStats();
		void ResetStats();

	private:
		Shader* shader;
		unsigned int VAO;
		unsigned int DrawCalls=0;

		void InitRenderData();
	};
}
#endif // !SPRITE_RENDERER_H


