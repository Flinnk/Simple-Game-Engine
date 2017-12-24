#pragma once
#include <Engine\Graphics\VertexBuffer.h>
#include <Engine\Graphics\VertexBufferLayout.h>
namespace GameEngine
{
	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& Buffer, const VertexBufferLayout& Layout);
		void Bind();
		void Unbind();
	private:
		unsigned int ID = 0;
	};
}