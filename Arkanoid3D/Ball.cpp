#include "pch.h"
#include "Ball.h"

#include "Game.h"

float Ball::radius = 1.3f;

Ball::Ball(const std::string & modelPath, const std::string & texPath, EObjectType type, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale):
	GameObject(modelPath, texPath, type, pos, rot, scale),
	released(false),
	forward(glm::vec3(0, 0, 0)),
	power(8.f),
	startPos(pos)
{
	color = glm::vec3(0, 1, 0);
}

Ball::~Ball()
{
}

void Ball::Update(float deltaTime) 
{
	if (released) 
	{
		glm::vec3 newPos = transform->GetPos() + forward * deltaTime * power;
		
		std::pair<glm::vec3, glm::vec3> pair = Game::GetInstance().CheckCollision(transform->GetPos(), newPos, forward);
		forward = pair.second;
		transform->SetPos(pair.first + forward * deltaTime * power);

		if (glm::length(forward) == 0)
			released = false;
	}
}

void Ball::Release(const glm::vec3& playerPos)
{
	if (released)
		return;

	forward = glm::vec3(transform->GetPos() - playerPos);
	forward = glm::normalize(forward);

	released = true;
}

void Ball::OnHit(const glm::vec3 & vec)
{
	forward = glm::reflect(forward, vec);
}

void Ball::Reset()
{
	released = false;
	forward = glm::vec3(0, 0, 0);
	transform->SetPos(startPos);
}

void Ball::SetPos(float val)
{
	glm::vec3 tmp = transform->GetPos();
	tmp.x += val;
	transform->SetPos(tmp);
}