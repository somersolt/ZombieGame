#include "pch.h"
#include "SoundMgr.h"

SoundMgr::SoundMgr()
{
}

SoundMgr::~SoundMgr()
{
	Release();
}

void SoundMgr::Init(int totalChannels)
{
	Release();
	for (int i = 0; i < totalChannels; ++i)
	{
		waiting.push_back(new sf::Sound());
	}
}

void SoundMgr::Release()
{
	for (auto sound : waiting)
	{
		delete sound;
	}
	waiting.clear();
}

void SoundMgr::Update(float dt)
{
	const std::list<sf::Sound*>& list = playing;
	for (auto it = list.begin(); it != list.end(); )
	{
		sf::Sound* sound = *it;
		if (sound->getStatus() == sf::Sound::Status::Stopped)
		{
			waiting.push_back(sound);
			it = playing.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (isFading)
	{
		sf::Sound* Bgm = nullptr;
		sf::Sound* oldBgm = nullptr;
		crossFadeTimer += dt;


		Bgm = bgm->front();
		oldBgm = bgm->back();
		Bgm->setVolume(Bgm->getVolume() + (100 - 0) / crossFadeDuration * dt);
		oldBgm->setVolume(Bgm->getVolume() - (100 - 0) / crossFadeDuration * dt);

		if (crossFadeTimer > crossFadeDuration)
		{
			isFading = false;
			oldBgm->stop();
			bgm->pop_back();
			crossFadeTimer = 0;
		}

	}

}

void SoundMgr::PlayBgm(std::string id)
{
	sf::Sound* Bgm = nullptr;
	sf::Sound* oldBgm = nullptr;

	if (!bgm->empty())
	{
		isFading = true;
		oldBgm = bgm->front();
	}
		bgm->insert(bgm->begin(), Bgm);
		Bgm->setLoop(true);
		Bgm->setVolume(0);
		Bgm->play();
}

void SoundMgr::StopBgm()
{
}

void SoundMgr::PlaySfx(std::string id, bool loop)
{
	PlaySfx(RES_MGR_SOUND_BUFFER.Get(id), loop);
}

void SoundMgr::PlaySfx(sf::SoundBuffer& buffer, bool loop)
{
	sf::Sound* sound = nullptr;
	if (waiting.empty())
	{	
		sound = playing.front();
		playing.pop_front();
		sound->stop();

		sound->getStatus() == sf::SoundSource::Stopped;
	}
	else
	{
		sound = waiting.front();
		waiting.pop_front();
	}

	sound->setBuffer(buffer);
	sound->setLoop(loop);
	sound->setVolume(sfxVolume);
	sound->play();
	playing.push_back(sound);
}

void SoundMgr::StopAllSfx()
{
	for (auto sound : playing)
	{
		sound->stop();
		waiting.push_back(sound);
	}
	playing.clear();
}
