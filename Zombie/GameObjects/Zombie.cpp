#include "pch.h"
#include "Zombie.h"
#include "TileMap.h"
#include "SceneGame.h"

Zombie::Zombie(const std::string& name) : SpriteGo(name)
{
}

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie("zombie");
	zombie->type = zombieType;
	switch (zombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed =  100;
		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 20;
		zombie->speed = 50;
		break;
	}

	return zombie;
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	speed = Utils::RandomRange(30, 130);
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void Zombie::Update(float dt)
{
	if(!isDead)
	{
		SpriteGo::Update(dt);

		look = player->GetPosition() - position;
		Utils::Normalize(look);
		SetRotation(Utils::Angle(look));


		sf::Vector2f pos = position + look * speed * dt;
		if (sceneGame != nullptr)
		{
			pos = sceneGame->ClampByTileMap(pos);
		}
		SetPosition(pos);


	}

	if (isDead)
	{
		this->SetTexture("graphics/blood.png");
	}
	


	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	//} 좀비 삭제 테스트 코드

}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::SetZombieIsDead()
{
	isDead = true;
}
