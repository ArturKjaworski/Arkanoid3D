#pragma once

#include <glm/glm.hpp>
#include <iostream>

#include "ObjectLoader.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class Mesh
{
public:
	Mesh(const std::string& fileName);
	~Mesh();

	void Bind() const;
	void Unbind() const;

	GLuint GetIndicesCount() const { return indicesCount; }



private:

	void initMesh(const IndexedModel& model);

	GLuint indicesCount;
	IndexedModel indexedmodel;
	VertexArray va;
	VertexBuffer* vb;
	VertexBuffer* uv;
	IndexBuffer* ib;
};

