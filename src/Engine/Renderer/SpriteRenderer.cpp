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
#include <Engine\Utils\Log.h>
#include <Engine\Utils\Stopwatch.h>
#include <Engine\EngineMacros.h>
#include <Engine\Graphics\IndexBuffer.h>

namespace GameEngine {

	bool CompareFunction(const DrawCall2D& lhs, const DrawCall2D& rhs) { return (lhs.DrawCallIdentifier < rhs.DrawCallIdentifier); }


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

	void SpriteRenderer::Submit(const DrawCall2D& DrawCall) {

		Rect SpriteRect;

		float Width = 0;
		float Height = 0;

		if (DrawCall.UseTextureSize)
		{
			Width = DrawCall.Scale.x*DrawCall.Texture->GetWidth()*(DrawCall.Region.width - DrawCall.Region.x);
			Height = DrawCall.Scale.y*DrawCall.Texture->GetHeight()*(DrawCall.Region.height - DrawCall.Region.y);
		}
		else
		{
			Width = DrawCall.Scale.x*DrawCall.DrawWidth;
			Height = DrawCall.Scale.y*DrawCall.DrawHeight;
		}

		SpriteRect.x = DrawCall.Postion.x;
		SpriteRect.y = DrawCall.Postion.y;
		SpriteRect.width = Width;
		SpriteRect.height = Height;

		if (Rect::CheckOverlap(CameraRect, SpriteRect))
		{
			Sprites.push_back(DrawCall);
		}
	}

	void SpriteRenderer::Draw()
	{
		DrawCalls = 0;
		if (Sprites.size() > 0)
		{
			VertexData* buffer = (VertexData*)VBO->BeginWrite();
			std::stable_sort(Sprites.begin(), Sprites.end(), CompareFunction);
			int currentState = (*Sprites.begin()).DrawCallIdentifier;
			int indicesToDraw = 0;
			if (buffer)
			{
				const DrawCall2D* currentDrawCall = nullptr;
				for (const DrawCall2D& DrawCall : Sprites)
				{
					int elementKey = DrawCall.DrawCallIdentifier;
					//If different state finish writting draw previous state
					if (elementKey != currentState)
					{
						DrawBuffer(indicesToDraw, currentDrawCall->Texture);
						buffer = (VertexData*)VBO->BeginWrite();
						indicesToDraw = 0;
						currentState = elementKey;
					}

					currentDrawCall = &DrawCall;

					//Fill Buffer
					const TextureRegion uvRegion = DrawCall.Region;

					Vector3 position = DrawCall.Postion;



					Vector3 size = DrawCall.Scale;
					
					if (DrawCall.UseTextureSize)
					{
						size.x *= DrawCall.Texture->GetWidth()*(uvRegion.width - uvRegion.x);
						size.y *= DrawCall.Texture->GetHeight()*(uvRegion.height - uvRegion.y);
					}
					else
					{
						size.x *= DrawCall.DrawWidth;
						size.y *= DrawCall.DrawHeight;
					}
					
					
					Vector3 color = DrawCall.Color;


					//NOTE: To change to the default top left origin we have to change the uv y coordinate to y or height 

					buffer->position = Vector3(position.x, position.y + size.y, position.z);
					buffer->color = color;
					buffer->uv = Vector2(uvRegion.x, uvRegion.y);
					++buffer;

					buffer->position = Vector3(position.x + size.x, position.y, position.z);
					buffer->color = color;
					buffer->uv = Vector2(uvRegion.width, uvRegion.height);
					++buffer;

					buffer->position = position;
					buffer->color = color;
					buffer->uv = Vector2(uvRegion.x, uvRegion.height);
					++buffer;

					buffer->position = Vector3(position.x + size.x, position.y + size.y, position.z);
					buffer->color = color;
					buffer->uv = Vector2(uvRegion.width, uvRegion.y);
					++buffer;

					indicesToDraw += INDICES_PER_SPRITE;
					//If filled the buffer send draw call and start a new one
					if (indicesToDraw >= MAX_SPRITES * VERTEX_PER_SPRITE)
					{
						DrawBuffer(indicesToDraw, currentDrawCall->Texture);
						buffer = (VertexData*)VBO->BeginWrite();
						indicesToDraw = 0;
					}
				}
				if (indicesToDraw > 0)
				{
					DrawBuffer(indicesToDraw, currentDrawCall->Texture);
				}
			}

			Sprites.clear();
		}
	}

	void SpriteRenderer::DrawBuffer(int indicesToDraw, const Texture* texture)
	{
		Vector2 Size = Engine::GetInstance().GetDisplaySize();//TODO: Callback with Graphic context to be notified of resizing to adjust the viewport parameters
		Matrix4 ViewMatrix = Matrix4::Identity();

		Vector3 CameraPosition = CameraRef->GetAbsolutePosition();
		ViewMatrix *= Matrix4::Translation(CameraPosition*-1.0f);

		//Rotation base on the center pivot point
		//ViewMatrix *= Matrix4::Translation(Vector3(0.5f * size.x, 0.5f * size.y, 0.0f));
		//ViewMatrix *= Matrix4::Rotation(rotate, Vector3(0.0f, 0.0f, 1.0f));
		//ViewMatrix *= Matrix4::Translation(Vector3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		Camera CameraData = CameraRef->GetCameraData();

		Matrix4 PerspectiveMatrix;

		if (CameraData.Mode == CameraMode::ORTHOGRAPHIC)
		{
			//NOTE: To change to the default top left origin we have to flip the top and bottom values
			PerspectiveMatrix = Matrix4::Orthographic(0.0f, Size.x, 0.0f, Size.y, CameraData.NearPlane, CameraData.FarPlane);
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

	void SpriteRenderer::SetCamera(const CameraComponent* CameraPointer)
	{
		CameraRef = CameraPointer;
		Vector2 Size = Engine::GetInstance().GetDisplaySize();
		Vector3 position = CameraRef->GetAbsolutePosition();
		CameraRect.x = position.x;
		CameraRect.y = position.y;
		CameraRect.width = Size.x;
		CameraRect.height = Size.y;

	}
}