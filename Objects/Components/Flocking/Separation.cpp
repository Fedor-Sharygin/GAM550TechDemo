#include "pch.h"
#include "Separation.h"

#include "..//Components.h"
#include "..//..//GameObject.h"




glm::vec3 Separation::GetForwVectAddition()
{
	Transform* mTrans = mOwner->GetOwner()->GetComponent<Transform>();
	glm::vec3 mPos = mTrans->GetPosition();
	glm::vec2 mPosV2 = glm::vec2(mPos.x, mPos.z);

	std::vector<Component*>& allFlockers = mOwner->GetAllFlockers();
	glm::vec2 collect = glm::vec2(0.0f);
	float closeNum = 0.0f;
	for (auto& flo : allFlockers)
	{
		/// if we are checking the same body
		/// skip it
		if (flo == this->mOwner)
		{
			continue;
		}
		Transform* oTrans = flo->GetOwner()->GetComponent<Transform>();
		glm::vec3 oPos = oTrans->GetPosition();
		glm::vec2 oPosV2 = glm::vec2(oPos.x, oPos.z);

		float sqDist = glm::distance2(mPosV2, oPosV2);
		if (sqDist <= this->sqSepRadius)
		{
			closeNum += 1.0f;
			collect += mPosV2 - oPosV2;
		}
	}

	/// collect is guranteed to be 0.0f
	if (0.0f == closeNum)
	{
		return glm::vec3(0.0f);
	}

	collect = collect / closeNum;
	collect = glm::normalize(collect);
	glm::vec3 ret = glm::vec3(collect.x, 0.0f, collect.y);
	return ret;
}


