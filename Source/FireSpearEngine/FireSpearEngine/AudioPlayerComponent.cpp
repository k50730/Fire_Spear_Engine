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


void AudioPlayerComponent::Stop()
{
	sound.stop();
}

void AudioPlayerComponent::IsLoop(bool loop)
{
	sound.setLoop(loop);
}

void AudioPlayerComponent::SetVolume(float volume)
{
	sound.setVolume(volume);
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
