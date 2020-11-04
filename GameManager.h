#pragma once

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include ".//Managers//Events//Events.h"
#include ".//Objects//GameObject.h"
#include ".//Managers//EventManager.h"

class Manager;
enum class MANAGER_TYPE;

class Component;
enum class COMPONENT_TYPE;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update();
	void FrameStart();
	void FrameEnd();

	GameObject* CreateGameObject();
	
	template<typename TComp>
	TComp* AddComponentTo(GameObject* go)
	{
		/// check if the provided type is child of Component
		if (false == std::is_base_of<Component, TComp>::value)
		{
			return nullptr;
		}

		TComp* retComp = go->AddComponent<TComp>();

		/// if we failed to add this component return nullptr
		if (nullptr == retComp)
		{
			return nullptr;
		}

		/// otherwise add this component to
		/// the corresponding manager and return it
		Manager* reqManager = gameManagers[CTtoMT[((Component*)retComp)->cType].first];
		reqManager->SubscribeComponent(retComp);
		dynamic_cast<EventManager*>(gameManagers[MANAGER_TYPE::TYPE_EVENT_MANAGER])->Subscribe(retComp, CTtoMT[((Component*)retComp)->cType].second);
		return retComp;
	};


	GLFWwindow* GetGameWindow();


	/// Used for demo of audio and model components
	/// size is used for different cases
	/// (for future demos)
	void Demo(size_t size);
public:
private:
private:
	/// save comp type to manager type and to event type
	std::map<COMPONENT_TYPE, std::pair<MANAGER_TYPE, EVENT_TYPE>> CTtoMT;
	std::vector<COMPONENT_TYPE> nonEssentailUpdates;

	/// saves all of the game objects
	std::vector<GameObject*> gameObjects;

	/// save all of the managers
	std::unordered_map<MANAGER_TYPE, Manager*> gameManagers;
};



#endif


