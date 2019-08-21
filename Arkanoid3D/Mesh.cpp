#include "pch.h"
#include "Mesh.h"

#include "ObjectLoader.h"
#include <vector>

Mesh::Mesh(const std::string & fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	initMesh(model);
}

Mesh::~Mesh()
{
	delete(vb);
	delete(ib);	
	delete(uv);
}

void Mesh::Bind() const
{
	va.Bind();
	ib->Bind();
}

void Mesh::Unbind() const
{
	va.Unbind();
	ib->Unbind();
}

void Mesh::initMesh(const IndexedModel & model)
{
	indicesCount = model.indices.size();

	vb = new VertexBuffer(&model.positions[0], model.positions.size() * sizeof(model.positions[0]), 1);

	VertexBufferLayout layout;
	layout.Push<float>(3);

	va.AddBuffer(*vb, layout);

/*	uv = new VertexBuffer(&model.texCoords[0], model.texCoords.size() * sizeof(model.texCoords[0]));

	VertexBufferLayout layout2;
	layout2.Push<float>(2);

	va.AddBuffer(*uv, layout2);*/
	
	ib = new IndexBuffer(&model.indices[0], model.indices.size());
}

