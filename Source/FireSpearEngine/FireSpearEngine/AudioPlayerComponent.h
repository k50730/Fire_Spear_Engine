#pragma once
#include "BaseComponent.h"
#include "SFML/Audio.hpp"

class AudioPlayerComponent : public BaseComponent
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;
public:
	AudioPlayerComponent();
	~AudioPlayerComponent();
	void PlaySoundFromFile(const std::string audioFile);
	void PlayMusicFromFile(const std::string musicFile);
	void Stop();
	
	void Awake();
	void Start();
	void Update(sf::Time t);
	void LateUpdate();
};