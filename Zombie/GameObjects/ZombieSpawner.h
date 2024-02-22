#pragma once
#include "GameObject.h"
#include "Zombie.h"

class ZombieSpawner : public GameObject
{
protected:
	std::vector<Zombie::Types> zombieTypes;

	float interval = 1.f;  // 생성주기
	int spawnCount = 1; // 한번에 생성될 개수
	float radius = 250.f; //생성반경

	float timer = 0.f;

public:
	ZombieSpawner(const std::string& name = "");
	 ~ZombieSpawner() override = default;

	 void startWave(int spawncount);

	 void Init() override;
	 void Release() override;

	 void Reset() override;

	 void Update(float dt) override;
};

