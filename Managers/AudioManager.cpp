#include "pch.h"
#include "AudioManager.h"

#include "..//Objects//Component.h"


AudioManager::AudioManager()
	:
	Manager(MANAGER_TYPE::TYPE_AUDIO_MANAGER),
	mSystem(nullptr)
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
	FMOD_RESULT result = FMOD::System_Create(&mSystem);
	if (FMOD_OK != result)
	{
		std::cerr << "FMOD Error! " << result << " " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}

	/// Initialize the system and check for errors
	result = mSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (FMOD_OK != result)
	{
		std::cerr << "FMOD Error! " << result << " " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

void AudioManager::End()
{
	if (nullptr != mSystem)
	{
		mSystem->release();
	}
}



void AudioManager::Update(float dt)
{
	for (auto& audioComp : comps)
	{
		audioComp->Update(dt);
	}

	if (nullptr != mSystem)
	{
		mSystem->update();
	}
}



