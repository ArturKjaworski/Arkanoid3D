#pragma once


class VertexBuffer
{
public:
	VertexBuffer(const void* data, GLuint size, unsigned int bufferCount = 0);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:

	unsigned int rendererID;
};

