#pragma once 

#include <map>
#include <Engine\Math\Math.h>

namespace GameEngine {

	class Shader;
	struct Camera;
	struct Transform;

	struct Character {
		unsigned int TextureID;   
		Vector2 Size;
		Vector2 BaselineOffset;
		unsigned int NextCharacterHOffset;
	};
	
	class TextRenderer
	{
	public:
		std::map<char, Character> Characters;
		const Shader* TextShader;
		TextRenderer(Shader* shader);
		void Load(const std::string& font, unsigned int fontSize);
		void DrawText(const Transform* CameraTransform, const Camera* CameraData,const std::string& text, float x, float y, float scale,const Vector3& color);
		unsigned int GetDrawCallStats();
		void ResetStats();


	private:
		unsigned int VAO, VBO;
		unsigned int DrawCalls = 0;

	};
}
