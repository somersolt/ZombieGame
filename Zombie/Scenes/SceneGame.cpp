#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "Bullet.h"
#include "CrossHair.h"
#include "HpBar.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
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

	hpBar = new HpBar("hpBar");
	hpBar->SetSize({ (float)player->GetHp(), 50.f });
	hpBar->Reset();
	hpBar->SetOrigin(Origins::MC);
	HpBarPos.x *= 0.5f;
	HpBarPos.y -= 200.f;
	hpBar->SetPosition(HpBarPos);
	hpBar->SetColor(sf::Color::Red);
	AddGo(hpBar, Layers::Ui);

	CrossHair* crosshair = new CrossHair("crosshair");
	AddGo(crosshair);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	


	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = (sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f;

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f ,0.f });
	uiView.setSize((windowSize));
	uiView.setSize((centerPos));

	tileMap->SetPosition({ 0.f ,0.f });
	tileMap->SetOrigin(Origins::TL);
	mapCenterPos = { tileMap->GetMapBounds().width / 2.f, tileMap->GetMapBounds().height / 2.f };
	player->SetPosition(mapCenterPos);
	spawners->SetPosition(mapCenterPos);

	//spawners->startWave(10);
	FindGoAll("zombie", zombieList);
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::shoot()
{
	//Bullet* bullet = nullptr;

	//if (unUsedBulletList.empty())
	//{
	//	bullet = new Bullet("");
	//	bullet->Init();

	//}
	//else
	//{
	//	bullet = unUsedBulletList.front();
	//	unUsedBulletList.pop_front();

	//}

	//bullet->SetActive(true);

	//bullet->SetPosition(player->GetPosition());

	//bullet->fire(player->GetLook(), 800.f);

	//usedBulletList.push_back(bullet);
	//AddGo(bullet);
}

void SceneGame::Update(float dt)
{
	FindGoAll("zombie", zombieList, Layers::World);

	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());
	hpBar->SetCurrSize({ (float)player->GetHp(), 50.f });

	
	if (InputMgr::GetMouseButton(sf::Mouse::Button::Left))
	{
		shoot();
	}


	//}	{
	//	Bullet* bullet = *it;
	//	if (!bullet->GetActive())
	//	{


	// 플레이어 - 좀비 충돌 처리 ( 체력 감소 )
	//for (auto zombieGo : zombieList)
	//{
	//	Zombie* zombie = dynamic_cast<Zombie*>(zombieGo);
	//	if (zombie->GetZombieBound().intersects(player->GetPlayerBound()) && !zombie->GetZombieIsDead())
	//	{
	//		hpBar->SetUnderAttack(true);
	//	}
	//	else
	//	{
	//		hpBar->SetUnderAttack(false);
	//	}
	//}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		spawners->startWave(20);
		FindGoAll("zombie", zombieList);
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

	// 게임 오버
	if (hpBar->GetPlayerHp() == 0)
	{
		// TODO 게임 오버 상태로
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		//hpBar->SetUnderAttack(true);

		//TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
		//tileMap->sortLayer = 1;
		//ResortGo(tileMap);
	}

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
