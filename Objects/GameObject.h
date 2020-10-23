#pragma once

#ifndef _GO_H_
#define _GO_H_

#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(float dt);
	void FrameStart();
	void FrameEnd();

	template<typename TComp>
	TComp* AddComponent()
	{
		/// check if the provided type is a child of Component
		if (false == std::is_base_of<Component, TComp>::value)
		{
			return nullptr;
		}

		/// if we already have this component => return it
		if (goComponents.end() != goComponents.find(std::type_index(typeid(TComp))))
		{
			auto a = goComponents[std::type_index(typeid(TComp))];
			return static_cast<TComp*>(a);
		}

		/// otherwise => create it, push it in, and return
		TComp* nComp = new TComp();
		goComponents[std::type_index(typeid(TComp))] = nComp;
		((Component*)nComp)->SetOwner(this);
		return nComp;
	};

	template<typename TComp>
	TComp* GetComponent()
	{
		/// check if the provided type is a child of Component
		if (false == std::is_base_of<Component, TComp>::value)
		{
			return nullptr;
		}

		/// if we don't have this component => return nullptr
		if (goComponents.end() == goComponents.find(std::type_index(typeid(TComp))))
		{
			return nullptr;
		}

		/// otherwise => return the found component
		return static_cast<TComp*>(goComponents[std::type_index(typeid(TComp))]);
	};
public:
private:
private:
	/// contains all of the object's components
	std::unordered_map<std::type_index, Component*> goComponents;
};


#endif



