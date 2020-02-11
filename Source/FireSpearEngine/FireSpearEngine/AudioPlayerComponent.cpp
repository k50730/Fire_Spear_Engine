#include "AudioPlayerComponent.h"

AudioPlayerComponent::AudioPlayerComponent() 
{
	id = BaseComponent::ComponentID::Audio;
}

AudioPlayerComponent::~AudioPlayerComponent()
{

}

void AudioPlayerComponent::PlaySoundFromFile(const std::string audioFile)
{
	buffer.loadFromFile(audioFile);
	if (!buffer.loadFromFile(audioFile))
		return;
	sound.setBuffer(buffer);
	sound.play();
}

void AudioPlayerComponent::PlayMusicFromFile(const std::string musicFile)
{
	music.openFromFile(musicFile);
	if (!music.openFromFile(musicFile))
		return;
	music.play();
}

void AudioPlayerComponent::Stop()
{
	sound.stop();
	music.stop();
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
