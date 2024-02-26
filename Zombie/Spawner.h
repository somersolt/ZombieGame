#pragma once
#include "GameObject.h"
class SceneGame;

class Spawner : public GameObject
{
protected:

	float interval = 0.f;  // �����ֱ�
	int spawnCount = 0; // �ѹ��� ������ ����
	float radius = 0.f; //�����ݰ�

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


