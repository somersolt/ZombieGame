#pragma once
#include "SpriteGo.h"
#include "Player.h"
#include "Bullet.h"

class TileMap;
class SceneGame;
class Zombie : public SpriteGo
{

public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler
	};
	static const int TOtalTypes = 3;
	static Zombie* Create(Types zombieType);

protected:
	Types type;
	int maxHp;
	float speed;
	int damage;
	float attackInterval;
	float timer = 0.f;

	TileMap* tileMap = nullptr;
	SceneGame* sceneGame = nullptr;

	int hp;
	sf::Vector2f look = { 1.0f, 0.f };
	Player* player;
	Bullet* bullet;
	Zombie(const std::string& name = "");

	bool isAlive = true;

public:
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


	const sf::FloatRect GetZombieBound() const { return sprite.getGlobalBounds(); }

	void OnDamage(int damage);
	void OnDie();

};

