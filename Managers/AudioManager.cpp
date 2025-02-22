#include "pch.h"
#include "AudioManager.h"

#include "..//Objects//Component.h"

#include "FrameRateManager.h"



#define ASSERT_RESULT(result)					\
	if(FMOD_OK != result)						\
	{											\
		std::cerr << "FMOD Error! " << result	\
			<< " " << FMOD_ErrorString(result)	\
			<< std::endl;						\
		exit(-1);								\
	}



AudioManager::AudioManager()
	:
	Manager(MANAGER_TYPE::TYPE_AUDIO_MANAGER),
	mSystem(nullptr), mChannelGroup(nullptr)
{
	Initialize();
}

AudioManager::~AudioManager()
{
	End();
}



void AudioManager::Initialize()
{
	/// Create the system and check if it worked
	ASSERT_RESULT(FMOD::System_Create(&mSystem));

	/// Initialize the system and check for errors
	ASSERT_RESULT(mSystem->init(512, FMOD_INIT_NORMAL, 0));

	/// Create the channel group
	ASSERT_RESULT(mSystem->createChannelGroup("inGameSFX", &mChannelGroup));

	allChannels = std::unordered_map<std::string, FMOD::Channel*>();
}

void AudioManager::End()
{
	for (auto& audioComp : comps)
	{
		delete audioComp;
	}
	comps.clear();

	if (nullptr != mSystem)
	{
		mSystem->release();
	}
}



void AudioManager::Update(float dt)
{
	/*
	* this was used to test the setPaused
	* fmod channel function
	if (FrameRateManager::frameCount % 120 == 0)
	{
		for (auto& [_, chan] : allChannels)
		{
			chan->setPaused(false);
		}
	}
	else if (FrameRateManager::frameCount % 60 == 0)
	{
		for (auto& [_, chan] : allChannels)
		{
			chan->setPaused(true);
		}
	}*/

	for (auto& audioComp : comps)
	{
		audioComp->Update(dt);
	}

	if (nullptr != mSystem)
	{
		mSystem->update();
	}
}



FMOD::System* AudioManager::GetSystem() const
{
	return mSystem;
}




void AudioManager::StartAudio(FMOD::Sound* pSound, std::string nChannelName, bool paused)
{
	/// look if passed channel name already exists
	/// if not => create a new channel and play sound there
	if (allChannels.end() == allChannels.find(nChannelName))
	{
		FMOD::Channel* nChannel = nullptr;
		ASSERT_RESULT(mSystem->playSound(pSound, mChannelGroup, paused, &nChannel));
		allChannels[nChannelName] = nChannel;
	}
	else	/// otherwise => play on existing channel
	{
		ASSERT_RESULT(mSystem->playSound(pSound, mChannelGroup, paused, &allChannels[nChannelName]));
	}
}



