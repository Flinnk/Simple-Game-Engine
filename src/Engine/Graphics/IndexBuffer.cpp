#include <Engine\Graphics\IndexBuffer.h>
#include <GL\glew.h>

namespace GameEngine
{
	IndexBuffer::IndexBuffer(const unsigned int* Indices, const unsigned int IndicesCount): Count(IndicesCount)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(unsigned int), Indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
}