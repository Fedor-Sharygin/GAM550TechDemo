#include "pch.h"
#include "Evade.h"

#include "SphereMover.h"

#include "..//Components.h"
#include "..//..//GameObject.h"



float LineSegmentVSStaticCircle(glm::vec2& stLS, glm::vec2& enLS, glm::vec2& cenCir, float sqRadius, glm::vec2* diff)
{
	glm::vec2 stTcen = cenCir - stLS;
	glm::vec2 dir = enLS - stLS;
	glm::vec2 dirN = glm::normalize(dir);

	float m = glm::dot(stTcen, dirN);
	if (m < 0 && glm::length2(stTcen) > sqRadius)
	{
		return -1.0f;
	}

	float distToLS = glm::length2(stTcen) - std::powf(m, 2.0f);
	if (distToLS > sqRadius)
	{
		return -1.0f;
	}

	float midInterChord = std::sqrtf(sqRadius - distToLS);
	float dirLen = glm::length(dir);
	float ti0 = (distToLS - midInterChord) / dirLen;
	float ti1 = (distToLS + midInterChord) / dirLen;

	if (ti0 < 0.0f || ti0 > 1.0f)
	{
		return -1.0f;
	}

	*diff = m * dirN - cenCir;

	return ti0;
}



glm::vec3 Evade::GetForwVectAddition()
{
	Transform* mTrans = mOwner->GetOwner()->GetComponent<Transform>();
	glm::vec3 mFront = mTrans->GetForward();
	glm::vec2 mFrontV2 = glm::vec2(mFront.x, mFront.z);
	glm::vec3 mPos = mTrans->GetPosition();
	glm::vec2 mPosV2 = glm::vec2(mPos.x, mPos.z);
	glm::vec2 endLS = mPosV2 + std::sqrtf(this->sqDist) * mFrontV2;
	float mRadius = std::sqrtf(mOwner->GetBody()->GetSquareRadius());

	std::vector<Component*>& allFlockers = mOwner->GetAllFlockers();
	glm::vec2 minDirection, saveMinDirection;
	SphereMover* minDistBody = nullptr;
	float minSqDist = FLT_MAX, minSqRad;
	for (auto& flo : allFlockers)
	{
		if (flo == this->mOwner)
		{
			continue;
		}
		Transform* oTrans = flo->GetOwner()->GetComponent<Transform>();
		glm::vec3 oPos = oTrans->GetPosition();
		glm::vec2 oPosV2 = glm::vec2(oPos.x, oPos.z);

		float sqDistance = glm::distance2(mPosV2, oPosV2);
		if (sqDistance <= this->sqDist && sqDistance < minSqDist)
		{
			SphereMover* oBody = static_cast<Flocker*>(flo)->GetBody();
			float nSqRad = std::powf(mRadius + std::sqrtf(oBody->GetSquareRadius()), 2.0f);
			float time = LineSegmentVSStaticCircle(mPosV2, endLS, oPosV2, nSqRad, &saveMinDirection);
			if (-1.0f != time)
			{
				minSqDist = sqDistance;
				minDirection = saveMinDirection;
				minDistBody = oBody;
				minSqRad = nSqRad;
			}
		}
	}

	if (nullptr == minDistBody)
	{
		return glm::vec3(0.0f);
	}

	minDirection = glm::normalize(minDirection);
	glm::vec2 evadeVectorV2 = minDirection * minSqRad * 1.3f;
	glm::vec3 evadeVector = glm::vec3(evadeVectorV2.x, 0.0f, evadeVectorV2.y);

	return evadeVector;
}




