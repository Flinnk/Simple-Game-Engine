#include <Engine\Graphics\Mesh.h>
#include <Engine\Graphics\VertexBuffer.h>
#include <Engine\Graphics\VertexArray.h>
#include <Engine\Graphics\VertexBufferLayout.h>

namespace GameEngine
{
	Mesh::Mesh(const void* Data, const unsigned int Size)
	{
		VBO = new VertexBuffer(Data, Size);
		VAO = new VertexArray();
		VertexBufferLayout Layout;
		Layout.PushFloat(3);
		Layout.PushFloat(3);
		Layout.PushFloat(2);
		VAO->AddBuffer(*VBO, Layout);
	}

	Mesh::~Mesh()
	{
		if (VAO)
			delete VAO;
		VAO = nullptr;

		if (VBO)
			delete VBO;
		VBO = nullptr;

	}

	void Mesh::Release()
	{

	}
}