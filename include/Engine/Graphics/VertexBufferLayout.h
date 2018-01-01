#pragma once

#include <vector>

namespace GameEngine
{
	struct VertexBufferElement
	{
		unsigned int Count;
		unsigned int Type;
		unsigned char Normalized;
		static unsigned int GetTypeSize(unsigned int Type);
		
	};

	class VertexBufferLayout
	{

	public:
		VertexBufferLayout() :Stride(0) {}

		void PushFloat(unsigned int Count);
		void PushUInt(unsigned int Count);
		void PushUChar(unsigned int Count);	

		inline unsigned int GetStride() const { return  Stride; }

		inline const std::vector<VertexBufferElement>& GetElements() const { return Elements; }

	private:
		std::vector<VertexBufferElement> Elements;
		unsigned int Stride = 0;
	};
}