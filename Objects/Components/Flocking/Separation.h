#pragma once

#ifndef _SEPARATION_H_
#define _SEPARATION_H_


class Flocker;

class Separation
{
public:
	Separation() : sqSepRadius(0.0f) {};

	void SetSquareRadius(float nRad) { sqSepRadius = nRad; };
	void PassOwner(Flocker* nFlock) { mOwner = nFlock; };

	glm::vec3 GetForwVectAddition(float dt);
public:
private:
private:
	float sqSepRadius;

	Flocker* mOwner;
};


#endif

