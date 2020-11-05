#include "pch.h"
#include "Allignment.h"

#include "..//Components.h"
#include "..//..//GameObject.h"


glm::vec3 Allignment::GetForwVectAddition(float dt)
{
	Transform* mTrans = mOwner->GetOwner()->GetComponent<Transform>();
	glm::vec3 mFront = mTrans->GetForward();
	glm::vec2 mFrontV2 = glm::vec2(mFront.x, mFront.z);
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
		if (sqDist <= this->sqAllRadius)
		{
			closeNum += 1.0f;
			glm::vec3 oFront = oTrans->GetForward();
			glm::vec2 oFrontV2 = glm::vec2(oFront.x, oFront.z);
			collect += oFrontV2;
		}
	}

	/// collect is guranteed to be 0.0f
	if (0.0f == closeNum)
	{
		return glm::vec3(0.0f);
	}

	collect = collect / closeNum;
	collect = glm::normalize(collect);
	glm::vec2 diff = (collect - mFrontV2) / 10.0f * dt;
	return glm::vec3(diff.x, 0.0f, diff.y);
}



