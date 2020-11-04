#include "pch.h"
#include "Wander.h"

#include "..//Components.h"
#include "..//..//GameObject.h"



glm::vec3 Wander::GetForwVectAddition()
{
	using Type = std::uniform_real_distribution<float>;

	const Type dist = Type(-20.0f, 20.0f);
	float angleAddVal = dist(generator);

	curAngle += angleAddVal;
	if (curAngle < -180.0f)
	{
		curAngle += 360.0f;
	}
	else if (curAngle > 180.0f)
	{
		curAngle -= 360.0f;
	}

	Transform* mTrans = mOwner->GetOwner()->GetComponent<Transform>();

	glm::vec3 mFront = mTrans->GetForward();
	mFront = glm::vec3(mFront.x, 0.0f, mFront.z);
	glm::vec3 mUp = mTrans->GetUp();

	glm::vec3 change = glm::rotate(mFront, curAngle, mUp) * std::sinf(alphaRange / 2.0f);
	return change;
}


