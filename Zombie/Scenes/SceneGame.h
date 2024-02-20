#pragma once
#include "Scene.h"

class Player;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;
	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

};

