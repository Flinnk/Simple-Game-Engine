#pragma once

namespace GameEngine
{

	class VertexBuffer
	{
	public:
		VertexBuffer(const void* Data, const unsigned int Size);
		~VertexBuffer();
		void Bind() const;
		void Unbind() const;

		//Temp method
		void Draw()const ;
	private:
		unsigned int ID = 0;
		unsigned int DataSize = 0;
	};

}