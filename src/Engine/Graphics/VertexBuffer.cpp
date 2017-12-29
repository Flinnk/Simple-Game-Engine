#include <Engine\Graphics\VertexBuffer.h>
#include <GL\glew.h>

namespace GameEngine
{

	VertexBuffer::VertexBuffer(const void* Data, const unsigned int Size) :DataSize(Size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW);
	}
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);

	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void VertexBuffer::Draw() const
	{
		glDrawArrays(GL_TRIANGLES, 0, DataSize/(sizeof(float)*8));
	}
}