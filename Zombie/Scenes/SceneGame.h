#pragma once
#include "Scene.h"

class Player;
class ZombieSpawner;
class ItemSpawner;

class TileMap;
class Bullet;
class HpBar;
class Zombie;
class UiHud;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	ZombieSpawner* spawners = nullptr;
	ItemSpawner* itemSpawners = nullptr;

	TileMap* tileMap = nullptr;
	sf::Vector2f mapCenterPos;


	std::list<Bullet*> usedBulletList;
	std::list<Bullet*> unUsedBulletList;

	int currentBullet;
	int totalBullet;

	int score;
	int highScore;
	int wave;

	bool waveSwitch = false;
	float waveTimer = 0;

	UiHud* hud;

	std::list<GameObject*> zombieList;

	sf::Vector2f HpBarPos = { 1920 / 2 , 900};
	HpBar* hpBar = nullptr;
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetZombieList() const { return zombieList; }

	UiHud* GetHud() const
	{
		return hud;
	}

	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	bool IsInTileMap(const sf::Vector2f& pos);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;


	void Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);


	void Draw(sf::RenderWindow& window);

};

