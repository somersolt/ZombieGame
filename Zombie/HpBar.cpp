#include "pch.h"
#include "HpBar.h"

HpBar::HpBar(const std::string& name) : GameObject(name)
{
}

void HpBar::Reset()
{
	hpBarCurrSize = hpBarMaxSize;
	hpBar.setSize(hpBarCurrSize);
}

void HpBar::SetValue(float value)
{
	if (value < 0.f)
	{
		value = 0.f;
	}
	if (value > hpBarMaxSize.x)
	{
		value = hpBarMaxSize.x;
	}

	// 회복시 사용
}

void HpBar::Update(float dt)
{
	GameObject::Update(dt);
	
	if (isUnderAttack)
	{
		hpBarCurrSize.x += hpBarSpeed * dt;
		hpBar.setSize(hpBarCurrSize);

		if (hpBarCurrSize.x <= 0.f)
		{
			hpBarCurrSize.x = 0.f;
		}
		if (hpBarCurrSize.x > hpBarMaxSize.x)
		{
			hpBarCurrSize.x = hpBarMaxSize.x;
		}
	}
}

void HpBar::SetPosition(const sf::Vector2f pos)
{
	hpBar.setPosition(pos);
}

void HpBar::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
	{
		preset = Origins::TL;
	}
	originPreset = preset;
	origin = Utils::SetOrigin(hpBar, originPreset);
}

void HpBar::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	hpBar.setOrigin(newOrigin);
}

void HpBar::SetSize(const sf::Vector2f size)
{
	hpBarMaxSize = size;
}

void HpBar::SetColor(sf::Color color)
{
	hpBar.setFillColor(color);
}

void HpBar::SetSpeed(float speed)
{
	hpBarSpeed = -hpBarMaxSize.x / Duration;
}

void HpBar::Draw(sf::RenderWindow& window)
{
	window.draw(hpBar);
}

void HpBar::SetUnderAttack(bool setisUnderAttack)
{
	isUnderAttack = setisUnderAttack;
}
