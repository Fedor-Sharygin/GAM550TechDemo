#pragma once


class Body;

enum class ShapeType
{
	TYPE_SPHERE,
	TYPE_OBB,
	TYPE_CYLINDER,
	TYPE_CONE,
	TYPE_NUM
};


class Shape
{
public:
	Shape() {};
	virtual ~Shape() {};

	ShapeType GetType() const { return shapeType; };
	void SetType(ShapeType nType) { shapeType = nType; };
public:
private:
private:
	ShapeType shapeType;
};


