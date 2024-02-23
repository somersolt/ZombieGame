#include "pch.h"
#include "Player.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Bullet.h"

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

	fireTimer += dt;
	if (isFiring && fireTimer > fireInterval)
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
	std::cout << FRAMEWORK.GetTime() << ": Fire" << std::endl;
	Bullet* bullet = new Bullet();
	bullet->Init();
	bullet->Reset();
	bullet->SetPosition(position);
	bullet->Fire(look, bulletSpeed, bulletDamage);
	sceneGame->AddGo(bullet);
}

void Player::OnDamage(int damage)
{
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
}
