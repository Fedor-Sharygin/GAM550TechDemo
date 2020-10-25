#pragma once

#ifndef _ACOMP_H_
#define _ACOMP_H_

#include "..//Component.h"


class AssetManager;
class AudioManager;

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

	void SetSound(std::string nName);
	FMOD::Sound* GetSound() const;

	void SetChannelName(std::string nCName);

	void PassLoader(AssetManager* nLoader);
	void PassMediaPlayer(AudioManager* nMediaPlayer);

	void StartAudio();
	void PauseAudio();
	void StopAudio();
public:
private:
private:
	bool playing;
	FMOD::Sound* mSound;
	
	AssetManager* loader;
	AudioManager* mediaPlayer;

	std::string mChannel;
};




#endif



