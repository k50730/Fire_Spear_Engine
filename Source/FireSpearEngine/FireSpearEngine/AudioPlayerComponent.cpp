#include "AudioPlayerComponent.h"

AudioPlayerComponent::AudioPlayerComponent() 
{
	id = BaseComponent::ComponentID::Audio;
	playSound = false;
	playMusic = false;
}

AudioPlayerComponent::~AudioPlayerComponent()
{

}

void AudioPlayerComponent::PlaySoundFromFile(std::string audioFile)
{
	buffer.loadFromFile(audioFile);
	if (!buffer.loadFromFile(audioFile))
		return;
	sound.setBuffer(buffer);
	sound.play();
	sound.stop();
	playSound = true;
}

void AudioPlayerComponent::PlayMusicFromFile(std::string musicFile)
{
	music.openFromFile(musicFile);
	if (!music.openFromFile(musicFile))
		return;
	music.play();
	playMusic = true;
}

void AudioPlayerComponent::Stop()
{
	if (playMusic)
		music.stop();
	if (playSound)
		sound.stop();
}

void AudioPlayerComponent::Awake()
{
}

void AudioPlayerComponent::Start()
{
}

void AudioPlayerComponent::Update(sf::Time t)
{
}

void AudioPlayerComponent::LateUpdate()
{
}
