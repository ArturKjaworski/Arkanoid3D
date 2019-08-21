#include "pch.h"
#include "GameObject.h"

#include "Transform.h"
#include "Mesh.h"
#include "Texture.h"

GameObject::GameObject(const std::string& modelPath, const std::string& texPath, EObjectType type, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	mesh = new Mesh(modelPath);
	tex = new Texture(texPath);
	transform = new Transform(pos, rot, scale);
	hitBoxSize = glm::vec3();
	color = glm::vec3(0.2,0.3,0.8);
	this->type = type;
}


GameObject::~GameObject()
{
}


void GameObject::Update(float deltaTime)
{

}

void GameObject::Bind() const
{
	mesh->Bind();
	tex->Bind();
}

void GameObject::Unbind() const
{
	mesh->Unbind();
	tex->Unbind();
}


GLuint GameObject::GetIndicesCount() const
{
	return mesh->GetIndicesCount();
}

void GameObject::OnHit()
{

}
