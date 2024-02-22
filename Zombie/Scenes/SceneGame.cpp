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

void SceneGame::Init()
{
	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	player = new Player("Player");
	AddGo(player);

	spawners = new ZombieSpawner();
	AddGo(spawners);

	sf::Vector2f hpSize(600.f, 50.f);
	hpBar = new HpBar("hpBar");
	hpBar->SetSize(hpSize);
	hpBar->SetSpeed(10);
	hpBar->Reset();
	hpBar->SetOrigin(Origins::ML);
	HpBarPos.x *= 0.5f;
	HpBarPos.y -= 200.f;
	hpBar->SetPosition(mapCenterPos);
	hpBar->SetColor(sf::Color::Red);
	AddGo(hpBar);

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

	spawners->startWave(10);
	FindGoAll("zombie", zombieList);
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::shoot()
{
	Bullet* bullet = nullptr;
	if (unUsedBulletList.empty())
	{
		bullet = new Bullet("");
		bullet->Init();
	}
	else
	{
		bullet = unUsedBulletList.front();
		unUsedBulletList.pop_front();
	}

	bullet->SetActive(true);
	bullet->SetPosition(player->GetPosition());
	bullet->fire(player->GetLook(), 800.f);
	usedBulletList.push_back(bullet);
	AddGo(bullet);
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());



	// 플레이어 - 외곽 타일 충돌 처리
	if (player->GetPosition().x < tileMap->GetMapBounds().left)
	{
		player->SetPosition({ tileMap->GetMapBounds().left, player->GetPosition().y });
	}
	if (player->GetPosition().x > tileMap->GetMapBounds().width)
	{
		player->SetPosition({ tileMap->GetMapBounds().width, player->GetPosition().y });
	}
	if (player->GetPosition().y < tileMap->GetMapBounds().top)
	{
		player->SetPosition({ player->GetPosition().x, tileMap->GetMapBounds().top });
	}
	if (player->GetPosition().y > tileMap->GetMapBounds().height)
	{
		player->SetPosition({ player->GetPosition().x, tileMap->GetMapBounds().height });
	}


	
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		shoot();
	}


	// 사용한 총알 회수
	for (auto it = usedBulletList.begin(); it != usedBulletList.end();)
	{
		Bullet* bullet = *it;
		if (!bullet->GetActive())
		{
			gameObjects.remove(*it);
			it = usedBulletList.erase(it);
			unUsedBulletList.push_back(bullet);
		}
		else
		{
			++it;
		}

		//회수하는김에 좀비 - 총알 충돌 처리
		for (auto zombieGo : zombieList)
		{
			Zombie* zombie = dynamic_cast<Zombie*>(zombieGo);
			if (bullet->GetBulletBound().intersects(zombie->GetZombieBound()) && !zombie->GetZombieIsDead())
			{
				zombie->SetZombieIsDead();
				bullet->SetActive(false);
			}
		}


	}

	// 플레이어 - 좀비 충돌 처리 ( 체력 감소 )
	for (auto zombieGo : zombieList)
	{
		Zombie* zombie = dynamic_cast<Zombie*>(zombieGo);
		if (zombie->GetZombieBound().intersects(player->GetPlayerBound()) && !zombie->GetZombieIsDead())
		{
			hpBar->SetUnderAttack(true);
		}
		else
		{
			hpBar->SetUnderAttack(false);
		}
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


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}
