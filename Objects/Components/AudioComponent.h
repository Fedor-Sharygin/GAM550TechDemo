#pragma once

#ifndef _ACOMP_H_
#define _ACOMP_H_

#include "..//Component.h"


class AssetManager;
class AudioManager;

enum class AUDIO_TYPE
{
	TYPE_MUSIC,
	TYPE_SFX,
	TYPE_DEFAULT
};

class AudioComponent : public Component
{
public:
	AudioComponent();
	virtual ~AudioComponent();

	virtual void Update(float dt) override;
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override;
	virtual void End() override;

	/// Create an event to change the volume(?)
	virtual void HandleEvent(Event* nEvent) override;

	void SetSound(std::string nName, FMOD_MODE soundLoadMode = FMOD_DEFAULT);
	FMOD::Sound* GetSound() const;

	void SetChannelName(std::string nCName);

	void PassLoader(AssetManager* nLoader);
	void PassMediaPlayer(AudioManager* nMediaPlayer);

	void StartAudio();
	void PauseAudio();
	void StopAudio();

	void SetAudioType(AUDIO_TYPE nType) { mType = nType; };
public:
private:
private:
	bool playing;
	FMOD::Sound* mSound;

	AUDIO_TYPE mType;
	
	AssetManager* loader;
	AudioManager* mediaPlayer;

	std::string mChannel;
};




#endif



