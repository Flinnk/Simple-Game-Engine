#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <gl\glew.h>

#include <Engine/Renderer/TextRenderer.h>

#include <Engine/Graphics/Shader.h>

#include <string>
#include <Engine/Core/Engine.h>
#include <Engine/Utils/Log.h>
#include <Engine\Renderer\Camera.h>
#include <Engine\Core\Transform.h>
#include <Engine\Components\CameraComponent.h>
#include <Engine\Math\Vector3.h>

namespace GameEngine {

	TextRenderer::TextRenderer(Shader* shader)
	{
		TextShader = shader;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	//TODO: Every Character creates a texture, create one single texture(Atlas) with glTexSubImage2D caching uv coordinates to save later on draw calls and memory
	void TextRenderer::Load(const std::string& font, unsigned int fontSize)
	{
		Characters.clear();

		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			Log("Could not init FreeType Library");

		FT_Face face;
		if (FT_New_Face(ft, font.c_str(), 0, &face))
			Log("Failed to load font");

		FT_Set_Pixel_Sizes(face, 0, fontSize);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (GLubyte c = 0; c < 128; ++c)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				Log("Failed to load Glyph");
				continue;
			}

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				texture,
				Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	void TextRenderer::DrawText(const CameraComponent* CameraComponent, const std::string& text, float x, float y, float scale, const Vector3& color)
	{
		Vector2 Size = Engine::GetInstance().GetDisplaySize();//TODO: Callback with Graphic context to be notified of resizing to adjust the viewport parameters
		Matrix4 ViewMatrix = Matrix4::Identity();

		Vector3 CameraPosition = CameraComponent->GetAbsolutePosition();
		ViewMatrix *= Matrix4::Translation(CameraPosition*-1.0f);

		//Rotation base on the center pivot point
		//ViewMatrix *= Matrix4::Translation(Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));
		//ViewMatrix *= Matrix4::Rotation(rotate, Vector3(0.0f, 0.0f, 1.0f));
		//ViewMatrix *= Matrix4::Translation(Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		Camera CameraData = CameraComponent->GetCameraData();
		CameraData.NearPlane += abs(CameraPosition.z);
		CameraData.FarPlane += abs(CameraPosition.z);
		Matrix4 PerspectiveMatrix;

		if (CameraData.Mode == CameraMode::ORTHOGRAPHIC)
		{
			PerspectiveMatrix = Matrix4::Orthographic(0.0f, Size.x, Size.y, 0.0f, CameraData.NearPlane, CameraData.FarPlane);
		}
		else
		{
			PerspectiveMatrix = Matrix4::Perspective(CameraData.FieldOfView, Size.x / Size.y, CameraData.NearPlane, CameraData.FarPlane);
		}

		TextShader->Use();
		TextShader->SetMatrix4("view", ViewMatrix);
		TextShader->SetMatrix4("projection", PerspectiveMatrix);
		TextShader->SetVector3("textColor", color);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			float xpos = x + ch.BaselineOffset.x * scale;
			float ypos = y + (Characters['H'].BaselineOffset.y - ch.BaselineOffset.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 },
				{ xpos,     ypos,       0.0, 0.0 },

				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 }
			};
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (ch.NextCharacterHOffset >> 6) * scale;
			++DrawCalls;
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int TextRenderer::GetDrawCallStats()
	{
		return DrawCalls;
	}

	void TextRenderer::ResetStats()
	{
		DrawCalls = 0;
	}

}