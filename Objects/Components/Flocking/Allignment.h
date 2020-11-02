#pragma once

#ifndef _ALLIGNMENT_H_
#define _ALLIGNMENT_H_


class Allignment
{
public:
	Allignment() : allRadius(0.0f) {};

	void SetRadius(float nRad) { allRadius = nRad; };

	glm::vec3 GetForwVectAddition();
public:
private:
private:
	float allRadius;
};


#endif

