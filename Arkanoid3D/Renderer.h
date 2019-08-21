#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"

class GameObject;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw(const std::vector<GameObject*>& gObjs, Camera* cam, Shader& shader);
	void Clear();

};

