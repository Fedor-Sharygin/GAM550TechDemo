#include "pch.h"
#include "AudioComponent.h"

#include "..//GameObject.h"

#include "..//..//Managers//Managers.h"



AudioComponent::AudioComponent()
	:
	Component(COMPONENT_TYPE::TYPE_AUDIO)
{
	Initialize();
}

AudioComponent::~AudioComponent()
{
	End();
}


void AudioComponent::Update(float dt)
{}


void AudioComponent::Initialize()
{
	mSound = nullptr;
	loader = nullptr;
	mediaPlayer = nullptr;
}

void AudioComponent::End()
{}


void AudioComponent::SetSound(std::string nName)
{
	mSound = loader->LoadSound(nName, mediaPlayer->GetSystem());
	if (nullptr == mSound)
	{
		std::cerr << "Error! Failed to load sound" << std::endl;
		exit(-1);
	}
}

FMOD::Sound* AudioComponent::GetSound() const
{
	return mSound;
}


void AudioComponent::PassLoader(AssetManager* nLoader)
{
	loader = nLoader;
}

void AudioComponent::PassMediaPlayer(AudioManager* nMediaPlayer)
{
	mediaPlayer = nMediaPlayer;
}


