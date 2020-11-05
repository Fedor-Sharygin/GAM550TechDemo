#pragma once

#ifndef _EVADE_H_
#define _EVADE_H_


/// Evade other bodies in front
/// of me at max distance dist

class Flocker;

class Evade
{
public:
	Evade() : sqDist(0.0f) {};

	void SetEvadeSquareDistance(float nDist) { sqDist = nDist; };
	void PassOwner(Flocker* nFlock) { mOwner = nFlock; };

	glm::vec3 GetForwVectAddition(float dt);
public:
private:
private:
	float sqDist;

	Flocker* mOwner;
};


#endif


