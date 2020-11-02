#include "pch.h"
#include "Wander.h"



glm::vec3 Wander::GetForwVectAddition()
{
	using Type = std::uniform_real_distribution<float>;

	const Type dist = Type(-10.0f, 3.0f);
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


}


