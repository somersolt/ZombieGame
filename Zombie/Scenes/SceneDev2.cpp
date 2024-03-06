#include "pch.h"
#include "SceneDev2.h"
#include "rapidcsv.h"
#include "ZombieTable.h"
#include "AniTest2.h"
#include "SpriteGo.h"

SceneDev2::SceneDev2(SceneIds id) : Scene(id)
{
}

SceneDev2::~SceneDev2()
{
}

void SceneDev2::Init()
{
	Scene::Init();

	background = new SpriteGo("");
	background->SetTexture("graphics/cillpenguin.png");
	AddGo(background);

	AddGo(new AniTest2());
}

void SceneDev2::Release()
{
	Scene::Release();
}

void SceneDev2::Enter()
{
	Scene::Enter();


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
		SceneMgr::Instance().ChangeScene(SceneIds::SceneDev1);
	}
}
