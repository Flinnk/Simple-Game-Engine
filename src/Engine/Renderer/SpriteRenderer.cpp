#include <Engine\Renderer\SpriteRenderer.h>
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
#include <algorithm>
#include <Engine\Components\SpriteComponent.h>
#include <Engine\Utils\Log.h>
#include <Engine\Utils\Stopwatch.h>
#include <Engine\EngineMacros.h>
#include <Engine\Graphics\IndexBuffer.h>

namespace GameEngine {

	bool CompareFunction(const SpriteComponent* lhs, const SpriteComponent* rhs) { return (lhs->GetRenderIdentifier() < rhs->GetRenderIdentifier()); }


	SpriteRenderer::SpriteRenderer(Shader *renderShader)
	{
		shader = renderShader;
		InitRenderData();
	}

	SpriteRenderer::~SpriteRenderer()
	{
		if (EBO)
			delete EBO;
		EBO = nullptr;

		if (VBO)
			delete VBO;
		VBO = nullptr;

		if (VAO)
			delete VAO;
		VAO = nullptr;
	}

	void SpriteRenderer::Submit(const SpriteComponent* component) {
		Sprites.push_back(component);
	}

	void SpriteRenderer::Draw(const CameraComponent* Camera)
	{
		DrawCalls = 0;
		if (Sprites.size() > 0)
		{
			VertexData* buffer = (VertexData*)VBO->BeginWrite();
			std::stable_sort(Sprites.begin(), Sprites.end(), CompareFunction);
			int currentState = (*Sprites.begin())->GetRenderIdentifier();
			int indicesToDraw = 0;
			if (buffer)
			{
				const SpriteComponent* currentSprite = nullptr;
				for (const SpriteComponent* Sprite : Sprites)
				{
					int elementKey = Sprite->GetRenderIdentifier();
					//If different state finish writting draw previous state
					if (elementKey != currentState)
					{
						DrawBuffer(Camera, indicesToDraw, currentSprite->GetTexture());
						buffer = (VertexData*)VBO->BeginWrite();
						indicesToDraw = 0;
						currentState = elementKey;
					}

					currentSprite = Sprite;

					//Fill Buffer
					Vector3 position = Sprite->GetAbsolutePosition();
					Vector3 size = Sprite->GetAbsoluteScale();
					size.x *= Sprite->GetTexture()->GetWidth();
					size.y *= Sprite->GetTexture()->GetHeight();
					Vector3 color = Sprite->GetTintColor();

					buffer->position = Vector3(position.x, position.y + size.y, position.z);
					buffer->color = color;
					buffer->uv = Vector2(0, 1);
					++buffer;

					buffer->position = Vector3(position.x + size.x, position.y, position.z);
					buffer->color = color;
					buffer->uv = Vector2(1, 0);
					++buffer;

					buffer->position = position;
					buffer->color = color;
					buffer->uv = Vector2(0, 0);
					++buffer;

					buffer->position = Vector3(position.x + size.x, position.y + size.y, position.z);
					buffer->color = color;
					buffer->uv = Vector2(1, 1);
					++buffer;

					indicesToDraw += INDICES_PER_SPRITE;
					//If filled the buffer send draw call and start a new one
					if (indicesToDraw >= MAX_SPRITES * VERTEX_PER_SPRITE)
					{
						DrawBuffer(Camera, indicesToDraw, currentSprite->GetTexture());
						(VertexData*)VBO->BeginWrite();
						indicesToDraw = 0;
					}
				}
				if (indicesToDraw > 0)
				{
					DrawBuffer(Camera, indicesToDraw, currentSprite->GetTexture());
				}
			}

			Sprites.clear();
		}
	}

	void SpriteRenderer::DrawBuffer(const CameraComponent* cam, int indicesToDraw, const Texture* texture)
	{
		Vector2 Size = Engine::GetInstance().GetDisplaySize();//TODO: Callback with Graphic context to be notified of resizing to adjust the viewport parameters
		Matrix4 ViewMatrix = Matrix4::Identity();

		Vector3 CameraPosition = cam->GetAbsolutePosition();
		ViewMatrix *= Matrix4::Translation(CameraPosition*-1.0f);

		//Rotation base on the center pivot point
		//ViewMatrix *= Matrix4::Translation(Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));
		//ViewMatrix *= Matrix4::Rotation(rotate, Vector3(0.0f, 0.0f, 1.0f));
		//ViewMatrix *= Matrix4::Translation(Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		Camera CameraData = cam->GetCameraData();

		Matrix4 PerspectiveMatrix;

		if (CameraData.Mode == CameraMode::ORTHOGRAPHIC)
		{
			PerspectiveMatrix = Matrix4::Orthographic(0.0f, Size.x, Size.y, 0.0f, CameraData.NearPlane, CameraData.FarPlane);
		}
		else
		{
			PerspectiveMatrix = Matrix4::Perspective(CameraData.FieldOfView, Size.x / Size.y, CameraData.NearPlane, CameraData.FarPlane);
		}

		shader->Use();
		shader->SetMatrix4("view", ViewMatrix);
		shader->SetMatrix4("projection", PerspectiveMatrix);
		VBO->EndWrite();
		VAO->Bind();

		texture->Use();
		EBO->Bind();
		EBO->Draw(indicesToDraw);
		++DrawCalls;
	}

	void SpriteRenderer::InitRenderData()
	{
		unsigned int indices[INDICES_SIZE];
		unsigned int offset = 0;
		for (int i = 0; i < INDICES_SIZE; i += INDICES_PER_SPRITE)
		{
			indices[i] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 1;

			offset += VERTEX_PER_SPRITE;
		}

		EBO = new IndexBuffer(indices, INDICES_SIZE);
		VAO = new VertexArray();
		VBO = new VertexBuffer(nullptr, BUFFER_SIZE, true);
		VertexBufferLayout layout;
		layout.PushFloat(3);
		layout.PushFloat(3);
		layout.PushFloat(2);
		VAO->AddBuffer(*VBO, layout);
	}

	unsigned int SpriteRenderer::GetDrawCallStats()
	{
		return DrawCalls;
	}

	void SpriteRenderer::ResetStats()
	{
		//DrawCalls = 0;
	}

}