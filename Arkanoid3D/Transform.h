#pragma once

#include <glm/gtx/rotate_vector.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0));

	glm::mat4 GetModel() const;
	
	glm::vec3& GetPos() { return pos; }
	glm::vec3& GetRot() { return rot; }
	glm::vec3& GetScale() { return scale; }

	void SetPos(const glm::vec3& vec);

private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};

