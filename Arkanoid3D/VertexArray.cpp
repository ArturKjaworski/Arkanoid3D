#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &rendererID);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (size_t ii = 0; ii< elements.size(); ++ii)
	{
		const auto& element = elements[ii];

		glEnableVertexAttribArray(ii);
		glVertexAttribPointer(0, element.count, element.type, 
			element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
