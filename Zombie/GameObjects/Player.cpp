#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name) : SpriteGo(name)
{
	textureId = "graphics/player.png";
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);

}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Reset()
{
	SpriteGo::Reset();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f mousePos = InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = mousePos;
	look = mouseWorldPos - position;
	Utils::Normalize(look);

	float angle = Utils::Angle(look);
	sprite.setRotation(angle);

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}

	SetPosition(position + direction * speed * dt);

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}