#include <Engine\Graphics\IndexBuffer.h>
#include <Engine\Graphics\OpenGL.h>

namespace GameEngine
{
	IndexBuffer::IndexBuffer(const unsigned int* Indices, const unsigned int IndicesCount) : Count(IndicesCount)
	{
		GLCall(glGenBuffers(1, &ID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(unsigned int), Indices, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &ID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));

	}

	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::Draw(unsigned int DrawCount)
	{
		int num = DrawCount > Count ? Count : DrawCount;
		GLCall(glDrawElements(GL_TRIANGLES, num, GL_UNSIGNED_INT, 0));
	}

}