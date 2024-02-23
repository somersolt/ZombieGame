#include "pch.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"
Bullet::Bullet(const std::string& name) : SpriteGo (name)
{
}

void Bullet::Fire(sf::Vector2f dir, float s, int d)
{
	direction = dir;
	speed = s;
	SetRotation(Utils::Angle(direction));
}

void Bullet::Init()
{
	GameObject::Init();
	SetTexture("graphics/bullet.png");
	SetOrigin(Origins::ML);
}

void Bullet::Update(float dt)
{
	GameObject::Update(dt);
	
	sf::Vector2f pos = position + direction * speed * dt;
	if (sceneGame != nullptr)
	{
		if (!sceneGame->IsInTileMap(position))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);
		}
	}

	SetPosition(pos);
}


void Bullet::Reset()
{
	SpriteGo::Reset();
	sprite.setScale({ 2.f , 2.f });
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

}

void Bullet::FixedUpdate(float dt)
{
	const std::list<GameObject*>& list = sceneGame->GetZombieList();
	for (auto go : list)
	{
		if (!go->GetActive())
		{
			continue;
		}

		if (GetGlobalBounds().intersects(go->GetGlobalBounds()))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);

			Zombie* zombie = dynamic_cast<Zombie*>(go);
			if (zombie != nullptr)
				zombie->OnDamage(10);

			break;
		}
	}
}