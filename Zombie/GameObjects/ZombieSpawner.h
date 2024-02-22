#pragma once
#include "GameObject.h"
#include "Zombie.h"

class ZombieSpawner : public GameObject
{
protected:
	std::vector<Zombie::Types> zombieTypes;

	float interval = 1.f;  // �����ֱ�
	int spawnCount = 1; // �ѹ��� ������ ����
	float radius = 250.f; //�����ݰ�

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

