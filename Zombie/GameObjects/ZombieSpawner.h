#pragma once
#include "Spawner.h"
#include "Zombie.h"

class SceneGame;

class ZombieSpawner : public Spawner
{
protected:
	std::vector<Zombie::Types> zombieTypes;

public:
	ZombieSpawner(const std::string& name = "");
	 ~ZombieSpawner() override = default;

	 void startWave(int spawncount);

	 GameObject* Create() override;

	 void Update(float dt) override;

	 void Reset() override;
};

