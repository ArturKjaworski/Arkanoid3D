#include "pch.h"
#include "Transform.h"

Transform::Transform(const glm::vec3 & pos, const glm::vec3 & rot, const glm::vec3 & scale)
{
	this->pos = glm::vec3(pos);
	this->rot = glm::vec3(rot);
	this->scale = glm::vec3(scale);
}

glm::mat4 Transform::GetModel() const
{
	glm::mat4 posMat(1);
	posMat = glm::translate(posMat, pos);
	glm::mat4 scaleMat(1);
	scaleMat = glm::scale(scaleMat, scale);

	glm::mat4 rotXMat(1);
	rotXMat = glm::rotate(rotXMat, glm::radians(rot.x), glm::vec3(1, 0, 0));
	glm::mat4 rotYMat(1);
	rotYMat = glm::rotate(rotYMat, glm::radians(rot.y), glm::vec3(0, 1, 0));
	glm::mat4 rotZMat(1);
	rotZMat = glm::rotate(rotZMat, glm::radians(rot.z), glm::vec3(0, 0, 1));

	glm::mat4 rotMat = rotXMat * rotYMat * rotZMat;

	return posMat * rotMat * scaleMat;
}

void Transform::SetPos(const glm::vec3& vec)
{
	pos = vec;
}
