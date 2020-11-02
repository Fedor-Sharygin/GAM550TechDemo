#pragma once

#ifndef _COHESION_H_
#define _COHESION_H_


class Cohesion
{
public:
	Cohesion() : cohRadius(0.0f) {};

	void SetRadius(float nRad) { cohRadius = nRad; };

	glm::vec3 GetForwVectAddition();
public:
private:
private:
	float cohRadius;
};


#endif


