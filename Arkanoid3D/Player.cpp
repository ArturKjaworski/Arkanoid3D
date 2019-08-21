#include "pch.h"
#include "Player.h"
#include "Ball.h"

Player::Player(Ball* ball, const std::string & modelPath, const std::string & texPath, EObjectType type, glm::vec3 pos, glm::vec3 rot, glm::vec3 scale):
	GameObject(modelPath, texPath, type, pos, rot, scale),
	ball(ball)
{
	hitBoxSize = glm::vec3(7.5, 0, 2.8);
	color = glm::vec3(1, 0, 0);
	score = 0;
}

Player::~Player()
{

}

void Player::MoveRight(float value)
{
	if ((transform->GetPos().x < -11 && (value < 0)) || (transform->GetPos().x > 11 && (value > 0)))
		return;

	if (!ball->IsReleased())
	{
		ball->SetPos(value / 1.3);
	}

	glm::vec3 tmp = transform->GetPos();
	tmp.x += value;
	transform->SetPos(tmp);
}

void Player::Shoot()
{
	if (!ball->IsReleased())
		ball->Release(transform->GetPos());
}

void Player::SetBall(Ball * ball)
{
	this->ball = ball;
}

void Player::AddToScore(int val)
{
	score += val;
}

void Player::Reset()
{
	transform->SetPos(glm::vec3(0,0,transform->GetPos().z));
	ball->Reset();
	score = 0;
}

