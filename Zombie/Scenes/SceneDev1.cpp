#include "pch.h"
#include "SceneDev1.h"
#include "rapidcsv.h"
#include "AniTest.h"

SceneDev1::SceneDev1(SceneIds id) : Scene(id)
{
}

SceneDev1::~SceneDev1()
{
}

void SceneDev1::Init()
{
	AddGo(new AniTest());

	Scene::Init();
}

void SceneDev1::Release()
{
	Scene::Release();
}

void SceneDev1::Enter()
{
	Scene::Enter();

	//StringTable* st = DT_MGR.Get<StringTable>(DataTable::Types::String);

}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::SceneDev2);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{

		std::cout << STRING_TABLE->Get("HI?") << std::endl;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		STRING_TABLE->Load(Languages::Korean);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		STRING_TABLE->Load(Languages::English);
	}
}
