#include "pch.h"
#include "ZombieSpawner.h"
#include "SceneGame.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	: Spawner(name)
{
}

void ZombieSpawner::Reset()
{
	Spawner::Reset();
	
	zombieTypes.clear();
	zombieTypes.push_back(Zombie::Types::Bloater);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Chaser);
	zombieTypes.push_back(Zombie::Types::Crawler);
	zombieTypes.push_back(Zombie::Types::Crawler);
}



void ZombieSpawner::startWave(int spawncount)
{
	for (int i = 0; i < spawncount; ++i)
	{
		sf::Vector2f pos = position + Utils::RandomInUnitCircle() * radius;
		Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
		Zombie* zombie = Zombie::Create(zombieType);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(pos);
		SCENE_MGR.GetCurrentScene()->AddGo(zombie);
	}
}

GameObject* ZombieSpawner::Create()
{
	Zombie::Types zombieType = zombieTypes[Utils::RandomRange(0, zombieTypes.size())];
	return Zombie::Create(zombieType);
}

void ZombieSpawner::Update(float dt)
{
}
