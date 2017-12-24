#pragma once

#include <vector>
#include <GL\glew.h>
#include <Engine\Utils\Assert.h>

namespace GameEngine
{
	struct VertexBufferElement
	{
		unsigned int Count;
		unsigned int Type;
		unsigned char Normalized;
		static unsigned int GetTypeSize(unsigned int Type)
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
	};

	class VertexBufferLayout
	{

	public:
		VertexBufferLayout() :Stride(0) {}

		template<class T>
		void Push(unsigned int Count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int Count)
		{
			Elements.push_back({ Count,GL_FLOAT,GL_FALSE });
			Stride += Count * VertexBufferElement::GetTypeSize(GL_FLOAT);
		}

		template<>
		void Push<unsigned int >(unsigned int Count)
		{
			Elements.push_back({ Count,GL_UNSIGNED_INT,GL_FALSE });
			Stride += Count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char >(unsigned int Count)
		{
			Elements.push_back({ Count,GL_UNSIGNED_BYTE,GL_TRUE });
			Stride += Count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);

		}

		inline unsigned int GetStride() const { return  Stride; }

		inline const std::vector<VertexBufferElement>& GetElements() const { return Elements; }

	private:
		std::vector<VertexBufferElement> Elements;
		unsigned int Stride = 0;
	};
}