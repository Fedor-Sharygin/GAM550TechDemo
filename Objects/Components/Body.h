#pragma once

#ifndef _BODY_H_
#define _BODY_H_

#include "..//Component.h"


class Shape;
enum class ShapeType;

class Body : public Component
{
public:
	Body()
		:
		Component(COMPONENT_TYPE::TYPE_BODY)
	{
		Initialize();
	};

	~Body()
	{
		End();
	};

	virtual void Update(float dt) override;
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override
	{
		bodyShape =nullptr;
		position = nextPosition = rotation =
			velocity = acceleration = sumOfForces = glm::vec3(0.0);
		mass = 0.0f;
		move = true;
		react = true;
	};
	virtual void End() override
	{
		delete bodyShape;
	};

	virtual void HandleEvent(Event* event) override;

	Shape* GetShape() const { return bodyShape; };

	void SetMass(float nMass) { mass = nMass; };
	float GetMass() const { return mass; };

	void SetMove(bool nMove) { move = nMove; };
	bool GetMove() const { return move; };

	void SetReact(bool nReact) { react = nReact; };
	bool GetReact() const { return react; };

	void ResetForces();
	void AddForce(glm::vec3 nForce);

	Shape* SetBodyShape(ShapeType nBodyShape);
public:
	glm::vec3 position;
	glm::vec3 nextPosition;
	glm::vec3 rotation;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 sumOfForces;
private:
private:
	Shape* bodyShape;
	
	float mass;	// for calculating the acceleration after applied forces
	bool move;	// defines whether or not the object moves in the world
	bool react;	// defines whether the body reacts to a collision
				// false == move is assumed by default unreactive

	/// currentFrameCollisions => store up the information with what bodies we have collisions this frame
	/// currentCollisions => store up with what collisions have been processed
	/// ___[body] == false => the collision with body has already been processed and didn't reappear => delete the registry
	/// ___[body] == true => the collision with body just appeared/reappeared => set it at false at the end of the process
	/// set ___[body] = true, if the collision appears or if the same body hit me twice in cosequent frames (do not process)
	std::vector<Body*> currentFrameCollisions;
	std::unordered_map<Body*, bool> processedCollisions;
};


#endif

