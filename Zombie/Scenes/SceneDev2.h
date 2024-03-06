#pragma once
class SpriteGo;

class SceneDev2 : public Scene
{
protected:

public:
	SceneDev2(SceneIds id);
	virtual ~SceneDev2();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	SpriteGo* background = nullptr;

};

