#include "pch.h"
#include "Block.h"

#include <iostream>

Block::Block(int id, const std::string & modelPath, const std::string & texPath, EObjectType type, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) :
	GameObject(modelPath, texPath, type, pos, rot, scale)
{
	this->id = id;
	hitBoxSize = glm::vec3(5.f,0.f, 7.5f);
	color = glm::vec3(0, 0, 1);
}

Block::~Block()
{
}

void Block::OnHit()
{

}
