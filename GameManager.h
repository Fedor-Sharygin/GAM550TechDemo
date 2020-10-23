#pragma once

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_


class Manager;
enum class MANAGER_TYPE;

class Component;
enum class COMPONENT_TYPE;

class GameObject;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update(float dt);
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
		gameManagers[CTtoMT[((Component*)retComp)->cType]]->SubscribeComponent(retComp);
		return retComp;
	}
public:
private:
private:
	/// save comp type to manager type
	std::map<COMPONENT_TYPE, MANAGER_TYPE> CTtoMT;

	/// saves all of the game objects
	std::vector<GameObject*> gameObjects;

	/// save all of the managers
	std::unordered_map<MANAGER_TYPE, Manager*> gameManagers;
};



#endif


