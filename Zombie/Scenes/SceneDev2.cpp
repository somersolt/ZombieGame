#include "pch.h"
#include "SceneDev2.h"
#include "rapidcsv.h"
#include "ZombieTable.h"

SceneDev2::SceneDev2(SceneIds id) : Scene(id)
{
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
}

void SceneDev2::Release()
{
	Scene::Release();
}

void SceneDev2::Enter()
{
	Scene::Enter();

	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).nameId << std::endl;
	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).maxHp << std::endl;
	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).speed << std::endl;
	std::cout << ZOMBIE_TABLE->Get(Zombie::Types::Bloater).damage << std::endl;

}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneGame);
	}
}
