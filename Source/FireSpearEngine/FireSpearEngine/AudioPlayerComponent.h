#pragma once
#include "BaseComponent.h"
#include "SFML/Audio.hpp"

class AudioPlayerComponent : public BaseComponent
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	AudioPlayerComponent();
	~AudioPlayerComponent();
	void PlaySoundFromFile(const std::string audioFile);
	void Stop();
	void IsLoop(bool);
	void SetVolume(float volume);
	
	void Awake();
	void Start();
	void Update(sf::Time t);
	void LateUpdate();
};