#pragma once
#include <string>
#include "Transform.h"


class Mesh;
class Texture;

class GameObject
{
public:

	static enum EObjectType
	{
		BG = 0,
		PLAYER,
		BLOCK,
		BALL
	}; 

	EObjectType type;

	GameObject(const std::string& modelPath, const std::string& texPath, EObjectType type, glm::vec3 pos = glm::vec3(), glm::vec3 rot = glm::vec3(), glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0));
	virtual ~GameObject();

	virtual void Update(float deltaTime);

	void Bind() const;
	void Unbind() const;

	virtual void OnHit();

	GLuint GetIndicesCount() const;

	Transform& GetTransform() const { return *transform; }

	const glm::mat4& GetModelMat() const { return transform->GetModel(); }

	const glm::vec3& GetHitBoxSize() const { return hitBoxSize; }


	glm::vec3 color;

protected:
	Transform* transform;
	Mesh* mesh;
	Texture* tex;
	glm::vec3 hitBoxSize;



};

