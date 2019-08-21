#include "pch.h"
#include "Renderer.h"
#include "gameObject.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const std::vector<GameObject*>& gObjs, Camera * cam, Shader& shader)
{
	shader.Bind();

	for (int ii = 0; ii < gObjs.size(); ++ii)
	{
		shader.SetUniform4f("u_Color", gObjs[ii]->color.x, gObjs[ii]->color.y, gObjs[ii]->color.z, 1.0);

		const glm::mat4 modelMat = gObjs[ii]->GetModelMat();
		glm::mat4 proj = cam->GetPerspViewProjection() * modelMat;
		shader.SetUniformMat4f("u_Transform", proj);

		gObjs[ii]->Bind();
	//	shader.SetUniform1i("u_Texture", 0);

		glDrawElements(GL_TRIANGLES, gObjs[ii]->GetIndicesCount(), GL_UNSIGNED_INT, 0);

		gObjs[ii]->Unbind();
	}
}
