#pragma once
#include "Scene.h"

class Player;
class ZombieSpawner;
class TileMap;
class Bullet;
class HpBar;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	ZombieSpawner* spawners = nullptr;
	TileMap* tileMap = nullptr;
	sf::Vector2f mapCenterPos;

	std::list<Bullet*> usedBulletList;
	std::list<Bullet*> unUsedBulletList;

	int currentBullet;
	int totalBullet;

	int score;
	int highScore;
	int wave;

	std::list<GameObject*> zombieList;

	sf::Vector2f HpBarPos = { 1920 / 2 , 900};
	HpBar* hpBar = nullptr;
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void shoot();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

};

