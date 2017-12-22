#include <Engine\Renderer\SpriteRenderer.h>
#include <GL\glew.h>
#include <Engine\Graphics\Shader.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\Math\Math.h>
#include <Engine\Core\Engine.h>
#include <Engine\Renderer\Camera.h>
#include <Engine\Core\Transform.h>

namespace GameEngine {

	SpriteRenderer::SpriteRenderer(Shader *renderShader)
	{
		shader = renderShader;
		InitRenderData();
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteVertexArrays(1, &VAO);
	}

	void SpriteRenderer::DrawTexture(const Transform* CameraTransform, const Camera* CameraData, const Texture *texture, Vector2 position,
		Vector2 size = Vector2(10, 10), float rotate = 0.0f,
		Vector3 color = Vector3(1.0f, 1.0f, 1.0f)) {

		shader->Use();
		Matrix4 model = Matrix4::Identity();

		model *= Matrix4::Translation(position);

		//Rotation base on the center pivot point
		model *= Matrix4::Translation(Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model *= Matrix4::Rotation(rotate, Vector3(0.0f, 0.0f, 1.0f));
		model *= Matrix4::Translation(Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		model *= Matrix4::Scale(size);

		Vector2 Size = Engine::GetInstance().GetDisplaySize();//TODO: Callback with Graphic context to be notified of resizing to adjust the viewport parameters

		shader->SetInteger("image", 0);

		Matrix4 ViewMatrix = Matrix4::Identity();
		ViewMatrix *= Matrix4::Translation(CameraTransform->Position);

		//Rotation base on the center pivot point
		//ViewMatrix *= Matrix4::Translation(Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));
		//ViewMatrix *= Matrix4::Rotation(rotate, Vector3(0.0f, 0.0f, 1.0f));
		//ViewMatrix *= Matrix4::Translation(Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		Matrix4 PerspectiveMatrix;

		if (CameraData->Mode == CameraMode::ORTHOGRAPHIC)
		{
			PerspectiveMatrix = Matrix4::Orthographic(0.0f, Size.x, Size.y, 0.0f, CameraData->NearPlane, CameraData->FarPlane);
		}
		else
		{
			PerspectiveMatrix = Matrix4::Perspective(CameraData->FieldOfView, Size.x / Size.y, CameraData->NearPlane, CameraData->FarPlane);
		}

		shader->SetMatrix4("view", ViewMatrix);
		shader->SetMatrix4("projection", PerspectiveMatrix);

		shader->SetMatrix4("model", model);

		shader->SetVector3("tintColor", color);

		glActiveTexture(GL_TEXTURE0);
		texture->Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		++DrawCalls;
	}

	void SpriteRenderer::InitRenderData()
	{
		unsigned int VBO;
		float vertices[] = {
			// Pos      // Tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	unsigned int SpriteRenderer::GetDrawCallStats()
	{
		return DrawCalls;
	}

	void SpriteRenderer::ResetStats()
	{
		DrawCalls = 0;
	}

}