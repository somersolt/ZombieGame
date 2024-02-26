#pragma once
#include "GameObject.h"
class SceneGame;

class Spawner : public GameObject
{
protected:

	float interval = 0.f;  // 생성주기
	int spawnCount = 0; // 한번에 생성될 개수
	float radius = 0.f; //생성반경

	float timer = 0.f;

	SceneGame* sceneGame = nullptr;

public:
	Spawner(const std::string& name = "");
	~Spawner() override = default;

	virtual GameObject* Create() = 0;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
};


