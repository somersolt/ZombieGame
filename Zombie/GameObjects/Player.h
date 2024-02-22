#pragma once
#include "SpriteGo.h"
class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.0f, 0.f };
	float speed = 500.f;

public:
	Player(const std::string& name = "");
	~Player() override = default;


	void Init();
	void Release();

	void Reset();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	const sf::Vector2f GetLook() const { return look; }
	const sf::FloatRect GetPlayerBound() const { return sprite.getGlobalBounds(); }

};

