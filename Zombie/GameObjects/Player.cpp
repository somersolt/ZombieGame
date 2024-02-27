#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "Item.h"
#include "UiHud.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
	textureId = "graphics/player.png";
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);

	isFiring = false;
	fireTimer = 3.f;

	hp = maxHp;
	ammo = magazine;
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
	look = mouseWorldPos - position;
	Utils::Normalize(look);

	SetRotation(Utils::Angle(look));

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2f pos = position + direction * speed * dt;
	
	if (sceneGame != nullptr)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}
	SetPosition(pos);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		isFiring = true;
	}

	if (InputMgr::GetMouseButtonUp(sf::Mouse::Left))
	{
		isFiring = false;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::R) && totalAmmo > 0)
	{
		if (!isAlive)
			return;

		ammo = magazine;
		totalAmmo -= magazine;
		sceneGame->GetHud()->SetAmmo(ammo, totalAmmo);

		if (totalAmmo < 0)
		{
			totalAmmo = 0;
		}
	}

	fireTimer += dt;

	if (isFiring && fireTimer > fireInterval && ammo > 0)
	{
		Fire();
		fireTimer = 0.f;
	}
	


}

void Player::FixedUpdate(float dt)
{

	DamageTimer += dt;

	const std::list<GameObject*>& list = sceneGame->GetZombieList();
	for (auto go : list)
	{
		if (!go->GetActive())
		{
			continue;
		}

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()) && DamageTimer > DamageInterval)
		{
			OnDamage(10);
			DamageTimer = 0.f;
		}
	}


}


void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Player::Fire()
{
	//std::cout << FRAMEWORK.GetTime() << ": Fire" << std::endl;
	Bullet* bullet = new Bullet("bullet");
	bullet->Init();
	bullet->Reset();
	bullet->SetPosition(position);
	bullet->Fire(look, bulletSpeed, bulletDamage);
	sceneGame->AddGo(bullet);

	SOUND_MGR.PlaySfx("sound/shoot.wav");

	if (isAlive)
	{
		ammo -= 1;
		sceneGame->GetHud()->SetAmmo(ammo, totalAmmo);
	}

}

void Player::OnDamage(int damage)
{

	sceneGame->GetHud()->SetHp(hp, maxHp);

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void Player::OnDie()
{
	SetTexture("graphics/chaser.png");
	fireInterval = 0.01f;
	sceneGame->GetHud()->SetHp(hp, maxHp);
	sceneGame->GetHud()->SetAmmo(9999, 9999);
	isAlive = false;
}

void Player::OnItem(Item* item)
{
	if (!isAlive)
		return;

	switch (item->GetType())
	{
	case Item::Types::Ammo:
		totalAmmo += item->GetValue();

		break;
	case Item::Types::Health:
		hp += item->GetValue();
		break;
	}
	sceneGame->GetHud()->SetHp(hp, maxHp);
	sceneGame->GetHud()->SetAmmo(ammo, totalAmmo);
}
