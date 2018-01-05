#include <Engine\Graphics\VertexBuffer.h>
#include <Engine\Graphics\OpenGL.h>

namespace GameEngine
{

	VertexBuffer::VertexBuffer(const void* Data, const unsigned int Size, bool dynamic) :DataSize(Size), Dynamic(dynamic)
	{
		GLCall(glGenBuffers(1, &ID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
	}
	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &ID));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));

	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	}

	void VertexBuffer::Draw() const
	{
		GLCall(glDrawArrays(GL_TRIANGLES, 0, DataSize / (sizeof(float) * 8)));
	}

	void* VertexBuffer::BeginWrite()
	{
		if (Dynamic)
		{
			Bind();
			return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}
		return nullptr;
	}

	void VertexBuffer::EndWrite()
	{
		if (Dynamic)
		{
			Bind();
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}
	}
}
