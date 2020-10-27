#pragma once

#include "Shape.h"


class Sphere : public Shape
{
public:
	Sphere() : radius(0.0) { SetType(ShapeType::TYPE_SPHERE); };
	virtual ~Sphere() {};

	void SetRadius(float nRadius) { radius = nRadius; };
	float GetRadius() const { return radius; };
public:
private:
private:
	float radius;
};


