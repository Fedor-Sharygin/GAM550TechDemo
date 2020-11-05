#pragma once

#ifndef _ALLIGNMENT_H_
#define _ALLIGNMENT_H_


class Flocker;

class Allignment
{
public:
	Allignment() : sqAllRadius(0.0f) {};

	void SetSquareRadius(float nRad) { sqAllRadius = nRad; };
	void PassOwner(Flocker* nFlock) { mOwner = nFlock; };

	glm::vec3 GetForwVectAddition(float dt);
public:
private:
private:
	float sqAllRadius;

	Flocker* mOwner;
};


#endif

