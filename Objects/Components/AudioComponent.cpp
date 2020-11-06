#include "pch.h"
#include "AudioComponent.h"

#include "Components.h"
#include "..//GameObject.h"

#include "..//..//Managers//Managers.h"
#include "..//..//Managers//Events//Events.h"



AudioComponent::AudioComponent()
	:
	Component(COMPONENT_TYPE::TYPE_AUDIO),
	mType(AUDIO_TYPE::TYPE_DEFAULT)
{
	Initialize();
}

AudioComponent::~AudioComponent()
{
	End();
}


void AudioComponent::Update(float dt)
{
	if (false == playing)
	{
		this->StartAudio();
		playing = true;
	}
}


void AudioComponent::Initialize()
{
	playing = false;
	mSound = nullptr;

	loader = nullptr;
	mediaPlayer = nullptr;
}

void AudioComponent::End()
{
	mSound->release();
	mSound = nullptr;
	mediaPlayer = nullptr;
	loader = nullptr;
}


void AudioComponent::SetSound(std::string nName, FMOD_MODE soundLoadMode)
{
	mSound = loader->LoadSound(nName, mediaPlayer->GetSystem(), soundLoadMode);
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


void AudioComponent::HandleEvent(Event* nEvent)
{
	/// if this object collided
	/// play the sound effect
	if (EVENT_TYPE::TYPE_CONTACT == nEvent->evType)
	{
		if (AUDIO_TYPE::TYPE_SFX == this->mType)
		{
			Body* mBody = this->GetOwner()->GetComponent<Body>();
			ContactEvent* tEvent = static_cast<ContactEvent*>(nEvent);
			/// only play the sfx if this object's body
			/// is one of the bodies in the contact
			if (mBody == tEvent->passedContact->GetBody1() || mBody == tEvent->passedContact->GetBody2())
			{
				this->StartAudio();
			}
		}
	}
}


void AudioComponent::SetChannelName(std::string nCName)
{
	mChannel = nCName;
}


void AudioComponent::PassLoader(AssetManager* nLoader)
{
	loader = nLoader;
}

void AudioComponent::PassMediaPlayer(AudioManager* nMediaPlayer)
{
	mediaPlayer = nMediaPlayer;
}



void AudioComponent::StartAudio()
{
	mediaPlayer->StartAudio(mSound, mChannel);
}

void AudioComponent::PauseAudio()
{}

void AudioComponent::StopAudio()
{}




