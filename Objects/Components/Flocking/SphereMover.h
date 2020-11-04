#pragma once

#ifndef _SPHEREMOVER_H_
#define _SPHEREMOVER_H_


class Transform;
class Flocker;

class SphereMover
{
public:
	SphereMover() : sphSqRadius(0.0f), mOwner(nullptr) {};

	void SetSquareRadius(float nRad) { sphSqRadius = nRad; };
	void PassOwner(Flocker* nFlock) { mOwner = nFlock; };

	float GetSquareRadius() const { return sphSqRadius; };
public:
private:
private:
	float sphSqRadius;

	Flocker* mOwner;
};


#endif


