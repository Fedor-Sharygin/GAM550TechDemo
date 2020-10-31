#include "pch.h"
#include "ParticleEmitter.h"

#include "Components.h"
#include "..//GameObject.h"

#include "..//..//Graphics//Particle.h"
#include "..//..//Graphics//Shader.h"

#include "..//..//Managers//GraphicsManager.h"
#include "..//..//Managers//AssetManager.h"


ParticleEmitter::ParticleEmitter()
	:
	Component(COMPONENT_TYPE::TYPE_PARTICLE_EMITTER)
{
    /// The only component that needs
    /// to be initialized after being created
	//Initialize();
}

ParticleEmitter::~ParticleEmitter()
{
	End();
}


void ParticleEmitter::Update(float dt)
{
    // update all particles
    for (unsigned int i = 0; i < this->maxParticleAmount; ++i)
    {
        Particle* p = this->particles[i];
        p->LifeTime -= dt; // reduce life
        if (p->LifeTime > 0.0f)
        {	// particle is alive, thus update
            p->Position -= p->Velocity * dt;
            p->Color.a -= dt * 2.5f;
        }
    }
}

void ParticleEmitter::FrameStart()
{}

void ParticleEmitter::FrameEnd()
{}


void ParticleEmitter::Initialize()
{
	drawer = nullptr;
	loader = nullptr;
	lastUsedParticle = 0;

    // set up mesh and attribute properties
    unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->partVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->partVAO);
    // fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);
    glBindVertexArray(0);

    // create this->amount default particle instances
    for (unsigned int i = 0; i < this->maxParticleAmount; ++i)
        this->particles.push_back(new Particle());
}

void ParticleEmitter::End()
{
	for (auto& particle : particles)
	{
		delete particle;
	}
	particles.clear();
	drawer = nullptr;
	loader = nullptr;
}


/// Only create particles when the object we are in was hit
void ParticleEmitter::HandleEvent(Event* nEvent)
{}


void ParticleEmitter::SetAmount(unsigned int nAmount)
{
    maxParticleAmount = nAmount;
}


void ParticleEmitter::Draw()
{
    // use additive blending to give it a 'glow' effect
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    drawer->prtShader->Use();
    for (auto& particle : this->particles)
    {
        if (particle->LifeTime > 0.0f)
        {
            drawer->prtShader->SetVec3("offset", particle->Position);
            drawer->prtShader->SetVec4("color", particle->Color);
			glBindTexture(GL_TEXTURE_2D, this->partVAO);
            glBindVertexArray(this->partVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    // don't forget to reset to default blending mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void ParticleEmitter::PassDrawer(GraphicsManager* nDrawer)
{
	drawer = nDrawer;
}

void ParticleEmitter::PassLoader(AssetManager* nLoader)
{
	loader = nLoader;
}

void ParticleEmitter::LoadTexture(std::string nName)
{
    textureName = nName;
    particleTexture = loader->LoadTexture(textureName);
}


unsigned int ParticleEmitter::FirstUnusedParticle()
{
    // first search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < this->maxParticleAmount; ++i) {
        if (this->particles[i]->LifeTime <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if (this->particles[i]->LifeTime <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle = 0;
    return 0;
}


void ParticleEmitter::RespawnParticle(Particle* nParticle, glm::vec3 offset, unsigned int frCount)
{
    Transform* ownTransform = this->GetOwner()->GetComponent<Transform>();
    float random = (((frCount + rand()) % 100) - 50) / 10.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    nParticle->Position = ownTransform->GetPosition() + random + offset;
    nParticle->Color = glm::vec4(rColor, rColor, rColor, 1.0f);
    nParticle->LifeTime = 1.0f;
    float vx = (((frCount + rand()) % 100) - 50) / 10.0f;
    float vy = (((frCount + rand()) % 100) - 50) / 10.0f;
    float vz = (((frCount + rand()) % 100) - 50) / 10.0f;
    nParticle->Velocity = glm::vec3(vx, vy, vz);
}


void ParticleEmitter::GenerateParticles(unsigned int newAmount, glm::vec3 offset, unsigned int frCount)
{
    // add new particles 
    for (unsigned int i = 0; i < newAmount; ++i)
    {
        int unusedParticle = this->FirstUnusedParticle();
        this->RespawnParticle(this->particles[unusedParticle], offset, frCount);
    }
}

