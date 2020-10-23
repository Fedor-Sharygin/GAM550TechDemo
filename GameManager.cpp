#include "pch.h"
#include "GameManager.h"

#include ".//Managers//Managers.h"
#include ".//Objects//GameObject.h"



GameManager::GameManager()
{
	CTtoMT = {
		{COMPONENT_TYPE::TYPE_AUDIO, MANAGER_TYPE::TYPE_AUDIO_MANAGER},
		{COMPONENT_TYPE::TYPE_BODY, MANAGER_TYPE::TYPE_PHYSICS_MANAGER}
	};

	GraphicsManager* mGrManager = new GraphicsManager();
	mGrManager->Initialize();

	AssetManager* mAssetManager = new AssetManager();
	mAssetManager->Initialize();

	FrameRateManager* mFRManager = new FrameRateManager();
	mFRManager->Initialize();

	InputManager* mInputManager = new InputManager(mGrManager->baseWindow);
	mInputManager->Initialize();

	gameManagers[mGrManager->mType] = mGrManager;
	gameManagers[mAssetManager->mType] = mAssetManager;
	gameManagers[mFRManager->mType] = mFRManager;
	gameManagers[mInputManager->mType] = mInputManager;
}

GameManager::~GameManager()
{}


void GameManager::Update(float dt)
{
	/// Update all of the managers
	for (auto& [_, man] : gameManagers)
	{
		man->Update(dt);
	}

	/// Update the rest of components in GO's
	for (auto& go : gameObjects)
	{
		go->Update(dt);
	}
}

void GameManager::FrameStart()
{
	/// FrameStart all of the managers
	for (auto& [_, man] : gameManagers)
	{
		man->FrameStart();
	}

	/// FrameStart the rest of components in GO's
	for (auto& go : gameObjects)
	{
		go->FrameStart();
	}
}

void GameManager::FrameEnd()
{
	/// FrameEnd all of the managers
	for (auto& [_, man] : gameManagers)
	{
		man->FrameEnd();
	}

	/// FrameEnd the rest of components in GO's
	for (auto& go : gameObjects)
	{
		go->FrameEnd();
	}
}


GameObject* GameManager::CreateGameObject()
{
	/// Create a new game object and return it
	GameObject* nGO = new GameObject();
	gameObjects.push_back(nGO);
	return nGO;
}



