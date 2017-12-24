#pragma once 

namespace GameEngine {

	class Shader;
	class Texture;
	struct Vector2;
	struct Vector3;
	class CameraComponent;
	class VertexArray;
	class VertexBuffer;

	class SpriteRenderer {
	public:
		SpriteRenderer(Shader *renderShader);
		~SpriteRenderer();

		void DrawTexture(const CameraComponent* Camera, const Texture *texture, Vector2 position,
			Vector2 size, float rotate,
			Vector3 color);

		unsigned int GetDrawCallStats();
		void ResetStats();

	private:
		Shader* shader;
		VertexArray* VAO;
		VertexBuffer* VBO;
		unsigned int DrawCalls=0;

		void InitRenderData();
	};
}


