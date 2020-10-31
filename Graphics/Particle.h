#pragma once

#ifndef _PARTICLE_H_
#define _PARTICLE_H_


struct Particle
{
	glm::vec3 Position, Velocity;
	glm::vec4 Color;
	float LifeTime;
	
	Particle()
		:
		Position(0.0f),
		Velocity(0.0f),
		Color(1.0f),
		LifeTime(0.0f)
	{};
};


#endif


