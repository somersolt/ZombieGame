#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));
	
	player = new Player("Player");
	AddGo(player);

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

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));

	tileMap->SetPosition(centerPos);
	tileMap->SetOrigin(Origins::MC);
	tileMap->SetRotation(45);

	player->SetPosition(centerPos);
	
	//player->SetPosition( { 500, 500 } );
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TOtalTypes);
		Zombie* zombie = Zombie::Create(zombieType);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f
			+ ((sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f)
		);

		AddGo(zombie);
	}


	for (auto obj : gameObjects) {
		Zombie* zombie = dynamic_cast<Zombie*>(obj);
		if (obj->GetActive()) {
			float distance = Utils::Magnitude(zombie->GetLook());
			if (distance < 10.f) {
				RemoveGo(obj);
				delete obj;
			}
		}
	}
}


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}
