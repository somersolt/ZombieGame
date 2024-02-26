#pragma once
#include "SpriteGo.h"
class SceneGame;
class TileMap;
class Item;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.0f, 0.f };
	float speed = 500.f;
	int bulletDamage = 0;

	int maxHp = 100;
	int hp = maxHp;

	int maxTotalAmmo = 48;
	int totalAmmo = maxTotalAmmo;
	int magazine = 6;
	int ammo = magazine;
	SceneGame* sceneGame = nullptr;

	bool isFiring = false;
	float bulletSpeed = 800.f;
	float fireInterval = 0.3f;
	float fireTimer = 0.f;

	float DamageInterval = 0.5f;
	float DamageTimer = 0.f;

	bool isAlive = true;

public:
	Player(const std::string& name = "");
	~Player() override = default;


	void Init();
	void Release();

	void Reset();

	void Update(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

	void Fire();

	const sf::Vector2f GetLook() const { return look; }
	const int GetHp() const { return hp; }
	const int GetAmmo() const { return ammo; }
	const int GetTotalAmmo() const { return totalAmmo; }
	const sf::FloatRect GetPlayerBound() const { return sprite.getGlobalBounds(); }

	void OnDamage(int damage);
	void OnDie();
	void OnItem(Item* item);

};

