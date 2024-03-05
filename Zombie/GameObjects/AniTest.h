#pragma once
#include "SpriteGo.h"
#include "Animator.h"

class AniTest : public SpriteGo
{
protected:
	Animator animator;

	float speed = 1000.f;
	sf::Vector2f velocity;
	bool isGrounded = true;
	const float gravity = 1500.f;

public:
	AniTest(const std::string& name = "");
	~AniTest() override = default;

	void TestInstance();
	void static TestStatic();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

	// void Draw(sf::RenderWindow& window) override;
};

