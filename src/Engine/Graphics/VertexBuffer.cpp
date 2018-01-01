#include <Engine\Graphics\VertexBuffer.h>
#include <Engine\Graphics\OpenGL.h>

namespace GameEngine
{

	VertexBuffer::VertexBuffer(const void* Data, const unsigned int Size) :DataSize(Size)
	{
		GLCall(glGenBuffers(1, &ID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW));
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
		GLCall(glDrawArrays(GL_TRIANGLES, 0, DataSize/(sizeof(float)*8)));
	}
}