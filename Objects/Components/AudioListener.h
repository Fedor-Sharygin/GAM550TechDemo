#pragma once

#ifndef _AUDIO_LISTENER_H_
#define _AUDIO_LISTENER_H_

#include "..//Component.h"


class ListenerAttributes
{
public:
	glm::vec3 prevPosition;
	glm::vec3 position;
};


class AudioListener : public Component
{
public:
	AudioListener();
	~AudioListener();

	virtual void Update(float dt) override;
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override;
	virtual void End() override;

	virtual void HandleEvent(Event* nEvent) override;
public:
private:
private:
	ListenerAttributes* mLAttributes;
};



#endif

