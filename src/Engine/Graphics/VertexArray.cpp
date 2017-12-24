#include <Engine\Graphics\VertexArray.h>

namespace GameEngine
{

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &ID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &ID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(ID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);

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
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, Element.Count, Element.Type, Element.Normalized, Layout.GetStride(), (const void*)Offset);
			Offset += Element.Count *VertexBufferElement::GetTypeSize(Element.Type);
		}
	}
}