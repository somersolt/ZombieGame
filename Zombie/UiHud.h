#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class SpriteGo;
class TextGo;

class UiHud : public GameObject
{
protected:
	std::string formatScore = "SCORE: ";
	std::string formatHiScore = "HIGH SCORE: ";
	std::string formatAmmo = "{0}/{1}";
	std::string formatWave = "WAVE: ";
	std::string formatZombieCount = "ZOMBIES: ";

	int score = 0;
	int hiScore = 0;
	int wave = 0;
	int zombieCount = 0;

	TextGo textScore;
	TextGo textHiScore;

	SpriteGo imgAmmoIcon;
	TextGo textAmmo;
	sf::RectangleShape gaugeHp;
	TextGo textWave;
	TextGo textZombieCount;

	sf::Vector2f gaugeHpSize = { 400.f , 70.f };

	sf::Vector2f referenceResolution = { 1920, 1080 } ;
	sf::Vector2f resolution = referenceResolution; 


public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResolution(const sf::Vector2f resolution);

	void SetScore(int s);
	void SetHiScore(int s);

	int GetScore() const { return score; }
	int GetHiScore() const { return hiScore; }
	int GetWave() const { return wave; }
	int GetZombieCount() const { return zombieCount; }

	void AddScore(int s);
	void NextWave(int w);

	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int w);
	void SetZombieCount(int count);


	void Init();
	void Release();
	void Reset();
	void Update(float dt);
	void LateUpdate(float dt);
	virtual void Draw(sf::RenderWindow& window);
};

