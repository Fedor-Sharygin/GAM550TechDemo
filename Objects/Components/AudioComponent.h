#pragma once

#ifndef _MCOMP_H_
#define _MCOMP_H_

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

	void PassLoader(AssetManager* nLoader);
	void PassMediaPlayer(AudioManager* nMediaPlayer);
public:
private:
private:
	FMOD::Sound* mSound;
	AssetManager* loader;
	AudioManager* mediaPlayer;
};




#endif



