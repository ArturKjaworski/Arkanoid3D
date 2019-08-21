#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball(const std::string& modelPath, const std::string& texPath, EObjectType type, glm::vec3 pos = glm::vec3(), glm::vec3 rot = glm::vec3(), glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0));
	virtual ~Ball();

	void Update(float deltaTime) override;
	void Release(const glm::vec3& playerPos);

	bool IsReleased() const { return released; }

	void SetPos(float val);
	void OnHit(const glm::vec3& vec);

	void Reset();

	static float radius;

private:
	bool released;

	glm::vec3 forward;

	float power;

	glm::vec3 startPos;
};

