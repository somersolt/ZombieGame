#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "UiHud.h"
#include "Bullet.h"
#include "CrossHair.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

void SceneGame::SetStatus(Status newStatus)
{
	currentStatus = newStatus;
	switch (currentStatus)
	{
	case SceneGame::Status::Playing:
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case SceneGame::Status::NextWave:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return Utils::Clamp(point, rect);
}

bool SceneGame::IsInTileMap(const sf::Vector2f& pos)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(pos);
}

void SceneGame::Init()
{
	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	player = new Player("Player");
	AddGo(player);

	spawners = new ZombieSpawner();
	AddGo(spawners);

	itemSpawners = new ItemSpawner();
	AddGo(itemSpawners);

	CrossHair* crosshair = new CrossHair("crosshair");
	crosshair->sortLayer = -1;
	AddGo(crosshair, Scene::Layers::Ui);

	hud = new UiHud();
	AddGo(hud, Layers::Ui);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = (sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f;

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f ,0.f });
	uiView.setSize((windowSize));
	uiView.setCenter((centerPos));

	tileMap->SetPosition({ 0.f ,0.f });
	tileMap->SetOrigin(Origins::TL);
	mapCenterPos = { tileMap->GetMapBounds().width / 2.f, tileMap->GetMapBounds().height / 2.f };
	player->SetPosition(mapCenterPos);
	spawners->SetPosition(mapCenterPos);
	itemSpawners->SetPosition(mapCenterPos);

	hud->SetHp(player->GetHp(), player->GetHp());
	hud->SetScore(0);
	hud->SetHiScore(0);
	hud->SetAmmo(player->GetAmmo(), player->GetTotalAmmo());
	hud->SetWave(wave);
	spawners->startWave(wave * 10);

	SetStatus(Status::Playing);

}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}


void SceneGame::Update(float dt)
{
	FindGoAll("zombie", zombieList, Layers::World);

	Scene::Update(dt);


	//worldView.setCenter(player->GetPosition());

	sf::Vector2f worldViewCenter = worldView.getCenter();
	worldViewCenter = Utils::Lerp(worldViewCenter, player->GetPosition(), dt * 0.5f);
	worldView.setCenter(worldViewCenter);

	// 카메라 선형보간

	if (hud->GetScore() > hud->GetHiScore())
	{
		hud->SetHiScore(hud->GetScore());
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{

		FindGoAll("zombie", zombieList);
		for (GameObject* obj : zombieList)
		{
		RemoveGo(obj);
		}
		zombieList.clear();
	}

	hud->SetZombieCount(zombieList.size());


	switch (currentStatus)
	{
	case SceneGame::Status::Playing:
		if (zombieList.size() == 0)
			SetStatus(Status::NextWave);
		break;
	case SceneGame::Status::NextWave:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			wave++;
			hud->SetWave(wave);
			spawners->startWave(wave * 10);
			SetStatus(Status::Playing);
		}
		break;
	}
	if (currentStatus == Status::NextWave)
	{
		FindGoAll("bullet", unUsedBulletList);
		for (auto obj : unUsedBulletList)
		{
			obj->SetActive(false);
		}
	}

	// 게임 오버

		// TODO 게임 오버 상태로
	
}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
