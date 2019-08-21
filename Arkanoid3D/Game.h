#pragma once

#include "GameObject.h"
#include "Ball.h"
#include "Block.h"
#include "Network.h"
#include "Player.h"

#include <vector>
#include <set>

class Game
{
public:
	Game();
	~Game();

	static Game& GetInstance();

	void Init();
	void InitMenu();

	void Update(float deltaTime);
	void UpdateState(const std::string& state);

	void SetGameToRunning(bool running);

	std::pair<glm::vec3, glm::vec3> CheckCollision(const glm::vec3& oldPos, const glm::vec3 & newPos, const glm::vec3& forwardVec);

	std::vector<GameObject*>& GetGameObjects() { return gObjects; }
	std::vector<int>& GetDestroyedObjsIDs() { return destroyedObjsID; }
	Player* GetPlayer() { return player; }
	bool IsRunning() { return isRunning; }

private:
	bool IsCollide(const glm::vec3& ballPos, GameObject* gObj);

	std::pair<std::vector<glm::vec3>, std::set<int>> ParseMsg(const std::string& state);

	float sendInterval = 0.0f;

	std::vector<GameObject*> gObjects;

	std::vector<int> destroyedObjsID;
	glm::vec3 minBoundary;
	glm::vec3 maxBoundary;

	Player* player;
	Player* enemy;

	bool isRunning = false;

};

