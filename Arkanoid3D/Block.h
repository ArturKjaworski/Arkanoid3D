#pragma once
#include "GameObject.h"

class Block : 
	public GameObject
{
public:
	Block(int id, const std::string& modelPath, const std::string& texPath, EObjectType type, glm::vec3 pos = glm::vec3(), glm::vec3 rot = glm::vec3(), glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0));
	virtual ~Block();

	void OnHit() override;

	int GetID() { return id; }

private:
	int id;

};

