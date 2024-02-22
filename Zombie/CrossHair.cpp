#include "pch.h"
#include "CrossHair.h"

CrossHair::CrossHair(const std::string& name) : SpriteGo(name)
{
	textureId = "graphics/crosshair.png";
}

void CrossHair::Release()
{
	SpriteGo::Release();
}

void CrossHair::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/crosshair.png");
	SetOrigin(Origins::MC);
}

void CrossHair::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
	SetPosition(mouseWorldPos);
}


void CrossHair::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}