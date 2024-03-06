#pragma once
class SpriteGo;
class AniTest2;

class SceneDev1 : public Scene
{
protected:

public:
	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	AniTest2* fox = nullptr;
	SpriteGo* background = nullptr;
};

