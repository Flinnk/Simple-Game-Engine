#include <Engine\Graphics\VertexBufferLayout.h>
#include <Engine\Graphics\OpenGL.h>
#include <Engine\Utils\Assert.h>

namespace GameEngine
{
	unsigned int VertexBufferElement::GetTypeSize(unsigned int Type)
	{
		switch (Type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
		}

		ASSERT(false);

		return 0;
	}

	void VertexBufferLayout::PushFloat(unsigned int Count)
	{
		Elements.push_back({ Count,GL_FLOAT,GL_FALSE });
		Stride += Count * VertexBufferElement::GetTypeSize(GL_FLOAT);
	}


	void VertexBufferLayout::PushUInt(unsigned int Count)
	{
		Elements.push_back({ Count,GL_UNSIGNED_INT,GL_FALSE });
		Stride += Count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
	}

	void VertexBufferLayout::PushUChar(unsigned int Count)
	{
		Elements.push_back({ Count,GL_UNSIGNED_BYTE,GL_TRUE });
		Stride += Count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);

	}
}