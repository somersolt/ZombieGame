#pragma once
#include "SpriteGo.h"
class HpBar : public GameObject
{
protected:
	sf::RectangleShape hpBar;
	sf::Vector2f hpBarMaxSize;
	sf::Vector2f hpBarCurrSize;
	float Duration = 10.f;
	float hpBarSpeed = -hpBarMaxSize.x / Duration;
	bool isUnderAttack = false;
	
	Scene::Layers layer = Scene::Layers::Ui;
public:

	HpBar(const std::string& name = "");
	void Reset() override;
	void SetValue(float value);


	void Update(float dt) override;

	void SetPosition(const sf::Vector2f pos);
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	void SetSize(const sf::Vector2f size);
	void SetColor(sf::Color color);
	void SetSpeed(float speed);

	void Draw(sf::RenderWindow& window) override;

	void SetUnderAttack(bool setisUnderAttack);

	const bool GetUnderAttack() const { return isUnderAttack; }
	const float GetPlayerHp() const { return  hpBarMaxSize.x; }

};

