#include <Engine\Renderer\SpriteRenderer.h>
#include <GL\glew.h>
#include <Engine\Graphics\Shader.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\Math\Math.h>
#include <Engine\Core\Engine.h>
#include <Engine\Renderer\Camera.h>
#include <Engine\Core\Transform.h>
#include <Engine\Graphics\VertexArray.h>
#include <Engine\Graphics\VertexBuffer.h>
#include <Engine\Graphics\VertexBufferLayout.h>
#include <Engine\Components\CameraComponent.h>

namespace GameEngine {

	SpriteRenderer::SpriteRenderer(Shader *renderShader)
	{
		shader = renderShader;
		InitRenderData();
	}

	SpriteRenderer::~SpriteRenderer()
	{
		delete VAO;
		delete VBO;
	}

	void SpriteRenderer::DrawTexture(const CameraComponent* CameraComponent, const Texture *texture, Vector2 position,
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
		Vector3 CameraPosition = CameraComponent->GetAbsolutePosition();

		ViewMatrix *= Matrix4::Translation(CameraPosition);

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

		shader->SetMatrix4("view", ViewMatrix);
		shader->SetMatrix4("projection", PerspectiveMatrix);

		shader->SetMatrix4("model", model);

		shader->SetVector3("tintColor", color);
		VAO->Bind();

		glActiveTexture(GL_TEXTURE0);
		texture->Use();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		VAO->Unbind();
		++DrawCalls;
	}

	void SpriteRenderer::InitRenderData()
	{
		float vertices[] = {
			// Pos      // Tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		VAO = new VertexArray();
		VBO = new VertexBuffer(&vertices, 24 * sizeof(float));
		VertexBufferLayout Layout;
		Layout.Push<float>(4);
		VAO->AddBuffer(*VBO, Layout);

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