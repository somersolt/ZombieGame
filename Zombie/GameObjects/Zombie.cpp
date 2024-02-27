#include "pch.h"
#include "Zombie.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "SpriteGoEffect.h"
#include "UiHud.h"
#include "ZombieTable.h"

Zombie::Zombie(const std::string& name) : SpriteGo(name)
{
}

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie("zombie");
	zombie->type = zombieType;

	const DataZombie& data = ZOMBIE_TABLE->Get(zombieType);
	zombie->textureId = data.textureId;
	zombie->maxHp = data.maxHp;
	zombie->speed = data.speed;
	zombie->damage = data.damage;
	zombie->attackInterval = data.attackInterval;

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
	hp = maxHp;
	speed = Utils::RandomRange(30, 130);
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	isAlive = true;
}

void Zombie::Update(float dt)
{
	if (!isAlive)
		return;
	
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

	


	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	//} 좀비 삭제 테스트 코드


void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Zombie::OnDamage(int damage)
{
	if (!isAlive)
		return;
	
	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Zombie::OnDie()
{
	if (!isAlive)
		return;
	
	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);
	sceneGame->GetHud()->AddScore(10);

	SpriteGoEffect* effectBlood = new SpriteGoEffect();
	effectBlood->Init();
	effectBlood->SetOrigin(Origins::MC);
	effectBlood->SetTexture("graphics/blood.png");
	effectBlood->Reset();
	effectBlood->sortLayer = -1;
	effectBlood->sortOrder = 1;

	effectBlood->SetPosition(position);
	effectBlood->SetRotation(Utils::RandomRange(0.f, 360.f));

	sceneGame->AddGo(effectBlood);
}
