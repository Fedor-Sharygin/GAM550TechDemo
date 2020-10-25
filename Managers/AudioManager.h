#pragma once

#ifndef _AMAN_H_
#define _AMAN_H_

#include "Manager.h"


class AudioManager : public Manager
{
public:
	AudioManager();
	virtual ~AudioManager();

	/// Maybe(?) do not override these functions
	/// depends on what I'll need to do
	virtual void Update(float dt) override;
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override;
	virtual void End() override;

	FMOD::System* GetSystem() const;
public:
private:
private:
	/// Audio studio
	FMOD::System* mSystem;
	FMOD::ChannelGroup* mChannelGroup;
};




#endif

