#pragma once 



namespace GameEngine
{
	class VertexBuffer;
	class VertexArray;

	class Mesh
	{
	public:

		Mesh(const void* Data, const unsigned int Size);
		virtual ~Mesh();

		Mesh(Mesh const&) = delete;
		Mesh(Mesh&&) = delete;
		Mesh& operator=(Mesh const&) = delete;
		Mesh& operator=(Mesh &&) = delete;
		void Release();
	public:
		VertexBuffer* VBO = nullptr;
		VertexArray* VAO = nullptr;
	};
}