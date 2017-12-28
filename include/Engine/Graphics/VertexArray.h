#pragma once
#include <Engine\Graphics\VertexBuffer.h>
namespace GameEngine
{
	class VertexBufferLayout;

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