#pragma once

#include "Shape.h"


class OBB : public Shape
{
public:
	OBB();
	virtual ~OBB() {};

	void SetHeight(float nHeight) { params[0] = nHeight; };
	float GetHeight() const { return params[0]; };

	void SetLength(float nLength) { params[1] = nLength; };
	float GetLength() const { return params[1]; };

	void SetWidth(float nWidth) { params[2] = nWidth; };
	float GetWidth() const { return params[2]; };

	void SetNormals(glm::vec3 nRotation);
	std::vector<glm::vec3>& GetNormals();
public:
	float params[3];
private:
private:
	std::vector<glm::vec3> normals;
};


