#pragma once
#include <vector>
#include <iostream>

struct VertexBufferElement
{
	GLuint type;
	GLuint count;
	GLubyte normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_UNSIGNED_INT: 
			case GL_FLOAT:			 return 4;
			case GL_UNSIGNED_BYTE:	 return 1;
		}
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() :
		stride(0) {}

	~VertexBufferLayout() {};

	template<typename T>
	void Push(unsigned int count)
	{
		std::cout << std::endl << "Wrong type!" << std::endl;
	}

	template<>
	void Push<float>(unsigned int count)
	{
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count *VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push <unsigned int> (unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push <unsigned char> (unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	const std::vector<VertexBufferElement>& GetElements() const { return elements; }
	unsigned int GetStride() const { return stride; }

private:
	std::vector<VertexBufferElement> elements;
	GLint stride;
};

