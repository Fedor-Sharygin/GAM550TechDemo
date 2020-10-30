#include "pch.h"
#include "GameManager.h"

#include ".//Graphics//Skybox.h"
#include ".//Managers//Managers.h"
#include ".//Objects//Components//Components.h"



GameManager::GameManager()
{
	CTtoMT = {
		{ COMPONENT_TYPE::TYPE_AUDIO,	std::make_pair(MANAGER_TYPE::TYPE_AUDIO_MANAGER, EVENT_TYPE::TYPE_DEFAULT) },
		{ COMPONENT_TYPE::TYPE_BODY,	std::make_pair(MANAGER_TYPE::TYPE_PHYSICS_MANAGER, EVENT_TYPE::TYPE_CONTACT) },
		{ COMPONENT_TYPE::TYPE_MODEL,	std::make_pair(MANAGER_TYPE::TYPE_GRAPHICS_MANAGER, EVENT_TYPE::TYPE_DEFAULT) }
	};

	GraphicsManager* mGrManager = new GraphicsManager();
	mGrManager->Initialize();

	AssetManager* mAssetManager = new AssetManager();
	mAssetManager->Initialize();
	mGrManager->skybox->PassLoader(mAssetManager);
	mGrManager->skybox->LoadFaces();

	FrameRateManager* mFRManager = new FrameRateManager();
	mFRManager->Initialize();

	InputManager* mInputManager = new InputManager(mGrManager->baseWindow);
	mInputManager->Initialize();

	AudioManager* mAudioManager = new AudioManager();
	EventManager* mEventManager = new EventManager();
	PhysicsManager* mPhysicsManager = new PhysicsManager();

	gameManagers[mFRManager->mType] = mFRManager;
	gameManagers[mInputManager->mType] = mInputManager;
	gameManagers[mEventManager->mType] = mEventManager;
	gameManagers[mGrManager->mType] = mGrManager;
	gameManagers[mAssetManager->mType] = mAssetManager;
	gameManagers[mAudioManager->mType] = mAudioManager;
	gameManagers[mPhysicsManager->mType] = mPhysicsManager;
	////// Test the push thing ///////
}

GameManager::~GameManager()
{
	for (auto& [_, man] : gameManagers)
	{
		delete man;
	}
	gameManagers.clear();
}


/// Consider that we only FrSt and FrE
/// with FrameRateManager and GraphicsManager
/// 
/// no need to update FrameRateManager

void GameManager::Update()
{
	float deltaTime = static_cast<FrameRateManager*>(gameManagers[MANAGER_TYPE::TYPE_FRAMERATE_MANAGER])->GetFrameTime();

	/// Update all of the managers
	for (auto& [type, man] : gameManagers)
	{
		if (MANAGER_TYPE::TYPE_FRAMERATE_MANAGER != type)
		{
			man->Update(deltaTime);
		}
	}

	/// Update the rest of components in GO's
	for (auto& go : gameObjects)
	{
		go->Update(deltaTime);
	}

	glfwPollEvents();
}

void GameManager::FrameStart()
{
	gameManagers[MANAGER_TYPE::TYPE_FRAMERATE_MANAGER]->FrameStart();
	gameManagers[MANAGER_TYPE::TYPE_GRAPHICS_MANAGER]->FrameStart();
}

void GameManager::FrameEnd()
{
	gameManagers[MANAGER_TYPE::TYPE_FRAMERATE_MANAGER]->FrameEnd();
	gameManagers[MANAGER_TYPE::TYPE_GRAPHICS_MANAGER]->FrameEnd();
}


GameObject* GameManager::CreateGameObject()
{
	/// Create a new game object and return it
	GameObject* nGO = new GameObject();
	gameObjects.push_back(nGO);
	return nGO;
}



GLFWwindow* GameManager::GetGameWindow()
{
	return static_cast<GraphicsManager*>(gameManagers[MANAGER_TYPE::TYPE_GRAPHICS_MANAGER])->baseWindow;
}




void GameManager::Demo(size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		this->CreateGameObject();
	}

	if (3 == size)
	{
		/// 1st object (0th)
		/// test the model loading and draw
		ModelComponent* fModComp = this->AddComponentTo<ModelComponent>(gameObjects[0]);
		Transform* fTrans = this->AddComponentTo<Transform>(gameObjects[0]);
		//Body* fBody = AddComponentTo<Body>(gameObjects[0]);

		fModComp->PassLoader(static_cast<AssetManager*>(gameManagers[MANAGER_TYPE::TYPE_ASSET_MANAGER]));
		fModComp->PassDrawer(static_cast<GraphicsManager*>(gameManagers[MANAGER_TYPE::TYPE_GRAPHICS_MANAGER]));
		fModComp->SetModel("nanosuit/nanosuit.obj");		/// find a model online and pass the name

		fTrans->SetPosition(glm::vec3(0.0f, 0.0f, -20.0f));
		fTrans->SetScale(glm::vec3((1.0f / 2.0f)));

		//fBody->SetMass(1.0f);

		/// 2nd object (1st)
		/// test the audio loading and play
		AudioComponent* sAudComp = this->AddComponentTo<AudioComponent>(gameObjects[1]);
		sAudComp->PassLoader(static_cast<AssetManager*>(gameManagers[MANAGER_TYPE::TYPE_ASSET_MANAGER]));
		sAudComp->PassMediaPlayer(static_cast<AudioManager*>(gameManagers[MANAGER_TYPE::TYPE_AUDIO_MANAGER]));
		sAudComp->SetSound("sample.wav", FMOD_LOOP_NORMAL);
		sAudComp->SetChannelName("sampleMusic");

		/// 3rd object (2nd)
		/// test the control
		ControlComponent* tContr = this->AddComponentTo<ControlComponent>(gameObjects[2]);
		tContr->PassControlee(static_cast<GraphicsManager*>(gameManagers[MANAGER_TYPE::TYPE_GRAPHICS_MANAGER]));
		tContr->PassInputStream(static_cast<InputManager*>(gameManagers[MANAGER_TYPE::TYPE_INPUT_MANAGER]));
	}
}


