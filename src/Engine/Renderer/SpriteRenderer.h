#pragma once 
#include <Engine\Math\Math.h>
#include <vector>
namespace GameEngine {

	struct VertexData
	{
		Vector3 position;
		Vector3 color;
		Vector2 uv;
	};


#define MAX_SPRITES 10000
#define VERTEX_PER_SPRITE 4
#define INDICES_PER_SPRITE 6
#define VERTEX_SIZE sizeof(VertexData)
#define SPRITE_SIZE VERTEX_SIZE * VERTEX_PER_SPRITE
#define BUFFER_SIZE SPRITE_SIZE * MAX_SPRITES
#define INDICES_SIZE MAX_SPRITES * INDICES_PER_SPRITE

	class Shader;
	class Texture;

	class CameraComponent;
	class VertexArray;
	class VertexBuffer;
	class SpriteComponent;

	class IndexBuffer;


	class SpriteRenderer {
	public:
		SpriteRenderer(Shader *renderShader);
		~SpriteRenderer();

		void Submit(const SpriteComponent* component);

		unsigned int GetDrawCallStats();
		void ResetStats();

		void Draw(const CameraComponent* Camera);

	private:
		void DrawBuffer(const CameraComponent* Camera, int verticesToDraw, const Texture* texture);
		std::vector<const SpriteComponent*> Sprites;
		Shader* shader;
		VertexArray* VAO;
		VertexBuffer* VBO;
		IndexBuffer* EBO;
		unsigned int DrawCalls = 0;

		void InitRenderData();
	};
}


