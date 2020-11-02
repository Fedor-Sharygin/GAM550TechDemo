#pragma once

#ifndef _SEPARATION_H_
#define _SEPARATION_H_


class Separation
{
public:
	Separation() : sepRadius(0.0f) {};

	void SetRadius(float nRad) { sepRadius = nRad; };

	glm::vec3 GetForwVectAddition();
public:
private:
private:
	float sepRadius;
};


#endif

