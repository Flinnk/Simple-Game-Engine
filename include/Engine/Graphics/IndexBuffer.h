#pragma once 

namespace GameEngine
{

	class IndexBuffer
	{
	public:
		IndexBuffer(const unsigned int* Indices, const unsigned int IndicesCount);
		~IndexBuffer();
		void Bind() const;
		void Unbind() const;
	private:
		unsigned int ID = 0;
		unsigned int Count = 0;
	};

}