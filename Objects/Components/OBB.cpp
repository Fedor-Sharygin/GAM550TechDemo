#include "pch.h"
#include "OBB.h"



OBB::OBB()
{
	SetType(ShapeType::TYPE_OBB);
	params[0] = params[1] = params[2] = 0.0;
	normals = {
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};
}

void OBB::SetNormals(glm::vec3 nRotation)
{
	glm::mat4 nNorms(1.0f);

	nNorms = glm::rotate(nNorms, params[0], glm::vec3(1.0f, 0.0f, 0.0f));
	nNorms = glm::rotate(nNorms, params[1], glm::vec3(0.0f, 1.0f, 0.0f));
	nNorms = glm::rotate(nNorms, params[2], glm::vec3(0.0f, 0.0f, 1.0f));

	normals[0] = glm::vec3(nNorms[0][0], nNorms[1][0], nNorms[2][0]);
	normals[1] = glm::vec3(nNorms[0][1], nNorms[1][1], nNorms[2][1]);
	normals[2] = glm::vec3(nNorms[0][2], nNorms[1][2], nNorms[2][2]);
}

std::vector<glm::vec3>& OBB::GetNormals()
{
	return normals;
}


