#include "pch.h"
#include "ParticleEmitter.h"

#include "..//GameObject.h"
#include "Components.h"

#include "..//..//Graphics//Shader.h"
#include "..//..//Managers//Managers.h"


ParticleEmitter::ParticleEmitter(unsigned int nAmount, unsigned int nSpawnRate, std::string nParticleTexture)
	:
	Component(COMPONENT_TYPE::TYPE_PARTICLE_EMITTER),
	particleAmount(nAmount),
	spawnRate(nSpawnRate),
	particleTextureName(nParticleTexture),
	lastUsedParticle(0),
	loader(nullptr)
{}

ParticleEmitter::~ParticleEmitter()
{
	loader = nullptr;
}


void ParticleEmitter::Update(float dt)
{
	/// add particles at the spawn rate
	for (int i = 0; i < spawnRate; ++i)
	{
		int unusedParticle = this->FirstUnusedParticle();
		this->RespawnParticle(this->particles[unusedParticle]);
	}
	/// update all particles, i.e. their positions
	for (auto& particle : particles)
	{
		particle.lifeTime -= dt;
		if (particle.lifeTime > 0.0f)
		{
			/// if the particle is still alive
			/// update its position and color
			particle.position += particle.velocity * dt;
			particle.color.a -= 2.5f * dt;
		}
	}
}

void ParticleEmitter::FrameStart()
{}

void ParticleEmitter::FrameEnd()
{}


void ParticleEmitter::Initialize()
{
	float particleQuad[] = {
		/// vertices			/// texture coords
		-0.5f,  0.5f,  0.0f,	0.0f,  1.0f,
		 0.5f,  0.5f,  0.0f,	1.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,	1.0f,  0.0f,

		-0.5f,  0.5f,  0.0f,	0.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,	1.0f,  0.0f,
		-0.5f, -0.5f,  0.0f,	0.0f,  0.0f,
	};
	glGenVertexArrays(1, &particleVAO);
	glGenBuffers(1, &particleVBO);
	glBindVertexArray(particleVAO);

	/// mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);

	/// set the mesh attributes
	/// 
	/// aPos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	/// aTexCoords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);

	glBindVertexArray(0);

	/// create as many particles as amount states
	for (int i = 0; i < particleAmount; ++i)
	{
		particles.push_back(Particle());
	}

	particleTexture = loader->LoadTexture(particleTextureName);
}

void ParticleEmitter::End()
{}


void ParticleEmitter::HandleEvent(Event* nEvent)
{}


void ParticleEmitter::Draw(Shader* pShader)
{
	// use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	pShader->Use();
	for (auto& particle : particles)
	{
		if (particle.lifeTime > 0.0f)
		{
			pShader->setVec3("position", particle.position);
			pShader->setVec4("color", particle.color);
			glUniform1i(glGetUniformLocation(pShader->ID, "particleTexture"), 0);
			glBindTexture(GL_TEXTURE_2D, particleTexture);
			glBindVertexArray(particleVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	// don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void ParticleEmitter::PassLoader(AssetManager* nLoader)
{
	loader = nLoader;
}

unsigned int ParticleEmitter::FirstUnusedParticle()
{
	// first search from last used particle, this will usually return almost instantly
	for (unsigned int i = lastUsedParticle; i < this->particleAmount; ++i) {
		if (this->particles[i].lifeTime <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// otherwise, do a linear search
	for (unsigned int i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].lifeTime <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

void ParticleEmitter::RespawnParticle(Particle& cParticle)
{
	float rColor = 0.5f + ((std::rand() % 100) / 100.0f);
	float rVelocity = 1.0f + ((std::rand() % 200 + 100) / 100.0f);

	cParticle.position = this->GetOwner()->GetComponent<Transform>()->GetPosition();
	cParticle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
	cParticle.lifeTime = 1.0f;
	cParticle.velocity = glm::vec3(rVelocity);
}


