#pragma once

#ifndef _SPHEREMOVER_H_
#define _SPHEREMOVER_H_


class Transform;

class SphereMover
{
public:
	SphereMover() : sphRadius(0.0f), mTrans(nullptr) {};

	void SetRadius(float nRad) { sphRadius = nRad; };
	void PassTransform(Transform* nTrans) { mTrans = nTrans; };
public:
private:
private:
	float sphRadius;
	Transform* mTrans;
};


#endif


