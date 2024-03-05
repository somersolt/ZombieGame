#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
	PingPong
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;

	AnimationFrame(const std::string& id, const sf::IntRect& coord)
		: textureId(id), texCoord(coord)
	{
	}

	const sf::Texture& GetTexture() const
	{
		return RES_MGR_TEXTURE.Get(textureId);
	}
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopType = AnimationLoopTypes::Single;
	int fps = 30;

	int GetTotalFrame() const
	{
		return frames.size();
	}

	bool loadFromFile(const std::string& filePath);
};

class Animator
{
protected:
	std::queue<std::string> queue;

	float speed = 1.f; // animationClip�� fps�� ����: 1.f�� ���, �״��

	bool isPlaying = false;
	int addFrame = 1;
	AnimationClip* currentClip = nullptr; // ���� ��� ���� �ִϸ��̼�
	int totalFrame = 0;
	int currentFrame = -1;
	float clipDuration = 0.f; // fps�� speed�� ���

	float accumTime = 0.f;

	sf::Sprite* target = nullptr; // �ִϸ��̼� ���

public:
	// ������, �Ҹ���
	Animator();
	~Animator();






	// Get, Set �Լ�
	bool IsPlaying() const { return isPlaying; }
	const std::string& GetCurrentClipId() { return currentClip->id; }

	sf::Sprite* GetTarget() const { return target; }
	void SetTarget(sf::Sprite* t) { target = t; }

	float GetSpeed() const { return speed; }
	void SetSpeed(float s) { speed = s; }

	void SetFrame(const AnimationFrame& frame);



	void Update(float dt);

	void Play(const std::string& clipId, bool clearQueue = true);
	void PlayQueue(const std::string& clipId);
	void Stop();
};

