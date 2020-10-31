#pragma once

#ifndef _PARTICLESMAN_H_
#define _PARTICLESMAN_H_

#include "Manager.h"


class ParticlesManager : public Manager
{
public:
	ParticlesManager();
	virtual ~ParticlesManager();

	virtual void Update(float dt) override;	/// Update all of the components associated with this manager
	virtual void FrameStart() override;		/// FrameStart all of the components associated with this manager
	virtual void FrameEnd() override;		/// FrameEnd all of the components associated with this manager

	virtual void Initialize() override;
	virtual void End() override;
public:
private:
private:
};


#endif


