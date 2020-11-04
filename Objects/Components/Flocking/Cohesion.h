#pragma once

#ifndef _COHESION_H_
#define _COHESION_H_


class Flocker;

class Cohesion
{
public:
	Cohesion() : sqCohRadius(0.0f) {};

	void SetSquareRadius(float nRad) { sqCohRadius = nRad; };
	void PassOwner(Flocker* nFlock) { mOwner = nFlock; };

	glm::vec3 GetForwVectAddition();
public:
private:
private:
	float sqCohRadius;

	Flocker* mOwner;
};


#endif


