#include <Engine\Graphics\VertexArray.h>
#include <Engine\Graphics\VertexBuffer.h>
#include <Engine\Graphics\VertexBufferLayout.h>
#include <Engine\Graphics\OpenGL.h>
namespace GameEngine
{

	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &ID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &ID));
	}

	void VertexArray::Bind()
	{
		GLCall(glBindVertexArray(ID));
	}

	void VertexArray::Unbind()
	{
		GLCall(glBindVertexArray(0));

	}

	void VertexArray::AddBuffer(const VertexBuffer& Buffer, const VertexBufferLayout& Layout)
	{
		Bind();
		Buffer.Bind();
		unsigned int Offset = 0;
		const std::vector<VertexBufferElement>& Elements = Layout.GetElements();
		for (unsigned int i = 0; i < Elements.size(); ++i)
		{
			const VertexBufferElement& Element = Elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, Element.Count, Element.Type, Element.Normalized, Layout.GetStride(), (const void*)Offset));
			Offset += Element.Count *VertexBufferElement::GetTypeSize(Element.Type);
		}
		Buffer.Unbind();
		Unbind();
	}
}