#pragma once
#include "BaseComponent.h"
#include "SFML/Audio.hpp"

class AudioPlayerComponent : public BaseComponent
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;
	bool playSound, playMusic;
public:
	AudioPlayerComponent();
	~AudioPlayerComponent();
	void PlaySoundFromFile(std::string audioFile);
	void PlayMusicFromFile(std::string musicFile);
	void Stop();
	
	void Awake();
	void Start();
	void Update(sf::Time t);
	void LateUpdate();
};