#include "pch.h"
#include "ParticlesManager.h"

#include "..//Objects//Components//Components.h"

#include "FrameRateManager.h"


ParticlesManager::ParticlesManager()
	:
	Manager(MANAGER_TYPE::TYPE_PARTICLES_MANAGER)
{}

ParticlesManager::~ParticlesManager()
{
	End();
}


void ParticlesManager::Update(float dt)
{
	for (auto& comp : comps)
	{
		ParticleEmitter* pComp = static_cast<ParticleEmitter*>(comp);
		pComp->GenerateParticles(rand() % 10 + 1, glm::vec3(0.0f), FrameRateManager::frameCount);
		pComp->Update(dt);
		pComp->Draw();
	}
}

void ParticlesManager::FrameStart()
{}

void ParticlesManager::FrameEnd()
{}


void ParticlesManager::Initialize()
{}

void ParticlesManager::End()
{
	for (auto& pem : comps)
	{
		delete pem;
	}
	comps.clear();
}

