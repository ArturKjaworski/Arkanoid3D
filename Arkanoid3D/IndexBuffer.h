#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const GLuint* data, GLuint count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint GetCount() const { return count; }

private:

	unsigned int rendererID;
	unsigned int count;
};

