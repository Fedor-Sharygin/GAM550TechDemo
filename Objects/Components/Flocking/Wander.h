#pragma once

#ifndef _WANDER_H_
#define _WANDER_H_


class Flocker;

/// Why make it harder? U - stoopid, Ted
/// just make 2d flocking/wander behavior
/// and add a random amount of up or down vector

class Wander
{
public:
	Wander() : alphaRange(0.0f), curAngle(0.0f), generator(), mOwner(nullptr) {};

	void SetHorRange(float nAR) { alphaRange = nAR; };
	void PassOwner(Flocker* nFlock) { mOwner = nFlock; };

	glm::vec3 GetForwVectAddition();
public:
private:
private:
	std::mt19937_64 generator;

	float alphaRange;
	float curAngle;

	Flocker* mOwner;
};


#endif
