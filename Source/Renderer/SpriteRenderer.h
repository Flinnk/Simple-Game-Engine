#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

namespace GameEngine {

	class Shader;
	class Texture;
	struct Vector2;
	struct Vector3;


	class SpriteRenderer {
	public:
		SpriteRenderer(Shader *renderShader);
		~SpriteRenderer();

		void DrawTexture(const Texture *texture, Vector2 position,
			Vector2 size, float rotate,
			Vector3 color) const;
	private:
		Shader* shader;
		unsigned int VAO;

		void InitRenderData();
	};
}
#endif // !SPRITE_RENDERER_H


