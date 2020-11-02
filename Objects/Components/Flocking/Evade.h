#pragma once

#ifndef _EVADE_H_
#define _EVADE_H_


/// Evade other bodies in front
/// of me at max distance dist

class Evade
{
public:
	Evade() : dist(0.0f) {};

	void SetEvadeDistance(float nDist) { dist = nDist; };

	glm::vec3 GetForwVectAddition();
public:
private:
private:
	float dist;
};


#endif


