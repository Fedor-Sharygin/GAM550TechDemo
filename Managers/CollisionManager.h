#pragma once

#include "..//Objects//Components//Shapes.h"

#ifndef _COLMAN_H_
#define _COLMAN_H_

class Body;

enum class ContactType
{
	TYPE_DYNAMIC_V_STATIC,
	TYPE_DYNAMIC_V_DYNAMIC,
	TYPE_DEFAULT
};

class Contact
{
public:
	Contact();
	~Contact();

	ContactType GetType() const { return cType; };
	void SetType(ContactType nCType) { cType = nCType; };

	Body* GetBody1() const { return b1; };
	Body* GetBody2() const { return b2; };
	void SetBodies(Body* nb1, Body* nb2);

	float GetTime() const { return time; };
	void SetTime(float nTime) { time = nTime; };
public:
private:
private:
	ContactType cType;
	float time;
	Body* b1;
	Body* b2;
};


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager() {};

	void CheckCollision(Body* b1, Body* b2, std::vector<Contact*>& contactStandIn);
public:
private:
private:
	void (*collisionFunctions[static_cast<unsigned>(ShapeType::TYPE_NUM)][static_cast<unsigned>(ShapeType::TYPE_NUM)])(Body* b1, Body* bs2, std::vector<Contact*>& contacts);
};


#endif

