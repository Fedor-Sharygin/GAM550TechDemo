#pragma once

#ifndef _WANDER_H_
#define _WANDER_H_


class Transform;

/// Why make it harder? U - stoopid, Ted
/// just make 2d flocking/wander behavior
/// and add a random amount of up or down vector

class Wander
{
public:
	Wander() : alphaRange(0.0f), curAngle(0.0f), generator() {};

	void SetHorRange(float nAR) { alphaRange = nAR; };
	void SetTransform(Transform* nTrans) { mTrans = nTrans; };

	glm::vec3 GetForwVectAddition();
public:
private:
private:
	std::mt19937_64 generator;

	float alphaRange;
	float curAngle;

	Transform* mTrans;
};


#endif
