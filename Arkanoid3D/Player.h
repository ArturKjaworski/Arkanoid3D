#pragma once
#include "GameObject.h"

class Ball;

class Player :
	public GameObject
{
public:
	Player(Ball* ball, const std::string& modelPath, const std::string& texPath, EObjectType type, glm::vec3 pos = glm::vec3(), glm::vec3 rot = glm::vec3(), glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0));
	virtual ~Player();

	void MoveRight(float value);

	void Shoot();

	void SetBall(Ball* ball);
	void AddToScore(int val);


	Ball* GetBall() { return ball; }
	int GetScore() { return score; }

	void Reset();

private:

	Ball* ball;
	int score;
};

