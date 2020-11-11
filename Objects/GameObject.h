#pragma once

#ifndef _GO_H_
#define _GO_H_

#include "Component.h"
#include "Components//Flocker.h"
#include "Components//Transform.h"
#include "Components//ParticleEmitter.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(float dt, std::vector<COMPONENT_TYPE> nonEssential);
	void FrameStart();
	void FrameEnd();

	template<typename TComp>
	TComp* AddComponent()
	{
		/// check if the provided type is a child of Component
		if (false == std::is_base_of<Component, TComp>::value)
		{
			return nullptr;
		}

		/// if we already have this component => return it
		if (goComponents.end() != goComponents.find(std::type_index(typeid(TComp))))
		{
			auto a = goComponents[std::type_index(typeid(TComp))];
			return static_cast<TComp*>(a);
		}

		/// otherwise => create it, push it in, and return
		TComp* nComp = new TComp();
		goComponents[std::type_index(typeid(TComp))] = nComp;
		((Component*)nComp)->SetOwner(this);
		return nComp;
	};

	template<>
	Flocker* AddComponent<Flocker>()
	{
		std::random_device seed;
		generator.seed(seed());
		if (goComponents.end() != goComponents.find(std::type_index(typeid(Flocker))))
		{
			auto a = goComponents[std::type_index(typeid(Flocker))];
			return static_cast<Flocker*>(a);
		}

		using Type = std::uniform_real_distribution<float>;

		float bodyRadius = 2.0f;
		float wanderAlpha = 10.0f;
		float sepRadius = 15.0f;
		float allRadius = 20.0f;
		float cohRadius = 20.0f;
		float evadeDistance = 5.0f;
		float velocity = 3.0f;
		float acceleration = 0.5f;

		Type brRand = Type(bodyRadius - 0.5f, bodyRadius + 0.5f);
		//Type waRand = Type(wanderAlpha - 0.5f, wanderAlpha + 0.5f);
		Type srRand = Type(sepRadius - 0.5f, sepRadius + 0.5f);
		Type arRand = Type(allRadius - 0.5f, allRadius + 0.5f);
		Type crRand = Type(cohRadius - 0.5f, cohRadius + 0.5f);
		Type edRand = Type(evadeDistance - 0.5f, evadeDistance + 0.5f);
		//Type veRand = Type(velocity - 0.5f, velocity + 0.5f);

		float nbr = brRand(generator);
		//float nwa = waRand(generator);
		float nsr = srRand(generator);
		float nar = arRand(generator);
		float ncr = crRand(generator);
		float ned = edRand(generator);
		//float nve = veRand(generator);

		glm::vec3 speed = this->GetComponent<Transform>()->GetForward() * velocity;
		Flocker* nFl = new Flocker(nbr, wanderAlpha, nsr, nar, ncr, ned, speed, acceleration);
		nFl->SetOwner(this);
		goComponents[std::type_index(typeid(Flocker))] = nFl;
		return nFl;
	};

	template<>
	ParticleEmitter* AddComponent<ParticleEmitter>()
	{
		if (goComponents.end() != goComponents.find(std::type_index(typeid(ParticleEmitter))))
		{
			auto a = goComponents[std::type_index(typeid(ParticleEmitter))];
			return static_cast<ParticleEmitter*>(a);
		}

		ParticleEmitter* nPE = new ParticleEmitter(200, 30, "awesomeface.png");
		nPE->SetOwner(this);
		goComponents[std::type_index(typeid(ParticleEmitter))] = nPE;
		return nPE;
	};

	template<typename TComp>
	TComp* GetComponent()
	{
		/// check if the provided type is a child of Component
		if (false == std::is_base_of<Component, TComp>::value)
		{
			return nullptr;
		}

		/// if we don't have this component => return nullptr
		if (goComponents.end() == goComponents.find(std::type_index(typeid(TComp))))
		{
			return nullptr;
		}

		/// otherwise => return the found component
		return static_cast<TComp*>(goComponents[std::type_index(typeid(TComp))]);
	};
public:
private:
private:
	/// contains all of the object's components
	std::unordered_map<std::type_index, Component*> goComponents;
	std::mt19937_64 generator;
};


#endif



