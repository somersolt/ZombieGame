#pragma once
#include "SpriteGo.h"
class CrossHair : public SpriteGo
{
protected:
public:
	CrossHair(const std::string& name = "");
	~CrossHair() override = default;

	void Init();
	void Release();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

