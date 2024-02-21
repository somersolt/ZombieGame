#pragma once
#include "SpriteGo.h"
#include "Player.h"
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

	int hp;
	sf::Vector2f look = { 1.0f, 0.f };
	Player* player;
	Zombie(const std::string& name = "");

public:
	~Zombie() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	const sf::Vector2f GetLook() const { return look; }

};

