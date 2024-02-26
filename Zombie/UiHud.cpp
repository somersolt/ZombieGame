#include "pch.h"
#include "UiHud.h"


UiHud::UiHud(const std::string& name) : GameObject(name)
{
}

void UiHud::SetResolution(const sf::Vector2f resolution)
{
}

void UiHud::SetScore(int s)
{
	textScore.SetString(formatScore + std::to_string(s));
}


void UiHud::SetHiScore(int s)
{
	textHiScore.SetString(formatHiScore + std::to_string(s));
}

void UiHud::AddScore(int s)
{
	score += s;
	SetScore(score);
}

void UiHud::NextWave(int w)
{
	wave = w + 1;
}

void UiHud::SetAmmo(int current, int total)
{
	textAmmo.SetString(std::to_string(current) + "/" + std::to_string(total));
}

void UiHud::SetHp(int hp, int max)
{
	float value = (float)hp / max;
	gaugeHp.setSize({ gaugeHpSize.x * value, gaugeHpSize.y });
}

void UiHud::SetWave(int w)
{
	textWave.SetString(formatWave + std::to_string(w));
}

void UiHud::SetZombieCount(int count)
{
	textZombieCount.SetString(formatZombieCount + std::to_string(count));
}

void UiHud::Init()
{
	textScore.Init();
	textHiScore.Init();
	imgAmmoIcon.Init();
	textAmmo.Init();
	textWave.Init();
	textScore.Init();

	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	
	float textSize = 60.f;
	textScore.Set(font, "", textSize, sf::Color::White);
	textHiScore.Set(font, "", textSize, sf::Color::White);
	textAmmo.Set(font, "", textSize, sf::Color::White);
	textWave.Set(font, "", textSize, sf::Color::White);
	textZombieCount.Set(font, "", textSize, sf::Color::White);
	
	imgAmmoIcon.SetTexture("graphics/ammo_icon.png");
	gaugeHp.setFillColor(sf::Color::Red);
	gaugeHp.setSize(gaugeHpSize);

	textScore.SetOrigin(Origins::TL);
	textHiScore.SetOrigin(Origins::TR);
	imgAmmoIcon.SetOrigin(Origins::BL);
	textAmmo.SetOrigin(Origins::BL);
	Utils::SetOrigin(gaugeHp, Origins::BL);
	textWave.SetOrigin(Origins::BR);
	textZombieCount.SetOrigin(Origins::BR);



	//Top
	float topY = 50.f;
	textScore.SetPosition({ 50.f , topY });
	textHiScore.SetPosition({ referenceResolution.x - 100.f , topY });

	//Bottom
	float BottomY = referenceResolution.y - 150.f;
	imgAmmoIcon.SetPosition({ 150.f , BottomY });
	textAmmo.SetPosition({ 400.f , BottomY });
	gaugeHp.setPosition({ 700.f , BottomY + 15 });
	textWave.SetPosition({ referenceResolution.x - 500.f , BottomY });
	textZombieCount.SetPosition({ referenceResolution.x - 150.f , BottomY });

}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	score = 0;
}

void UiHud::Update(float dt)
{
}

void UiHud::LateUpdate(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	textScore.Draw(window);
	textHiScore.Draw(window);
	textAmmo.Draw(window);
	textWave.Draw(window);
	textZombieCount.Draw(window);
	imgAmmoIcon.Draw(window);
	window.draw(gaugeHp);
}
