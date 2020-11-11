#pragma once

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "..//Component.h"


struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;

	glm::vec4 color;
	float lifeTime;

	Particle()
		:
		position(glm::vec3(0.0f)),	velocity(glm::vec3(0.0f)),
		color(glm::vec4(0.0f)),		lifeTime(-1.0f)	/// negative, so that they are not alive
													/// when they are first created
	{};
};

class Shader;

class AssetManager;
class GraphicsManager;

class ParticleEmitter : public Component
{
public:
	ParticleEmitter(unsigned int nAmount, unsigned int nSpawnRate, std::string nParticleTextureName);
	~ParticleEmitter();

	virtual void Update(float dt) override;
	virtual void FrameStart() override;
	virtual void FrameEnd() override;

	virtual void Initialize() override;
	virtual void End() override;

	virtual void HandleEvent(Event* nEvent) override;

	void Draw(Shader* pShader);

	void PassLoader(AssetManager* nLoader);
public:
private:
	unsigned int FirstUnusedParticle();
	void RespawnParticle(Particle& cParticle);
private:
	std::vector<Particle> particles;
	unsigned int spawnRate;
	unsigned int particleAmount;

	AssetManager* loader;

	unsigned int lastUsedParticle;
	unsigned int particleVAO, particleVBO;

	std::string particleTextureName;
	unsigned int particleTexture;
};



#endif


