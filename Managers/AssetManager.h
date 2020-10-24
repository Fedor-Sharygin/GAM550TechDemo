#pragma once

#ifndef _ASSET_H_
#define _ASSET_H_

#include "Manager.h"


class Model;

class AssetManager : public Manager
{
public:
	AssetManager();
	~AssetManager() = default;

	virtual void Update(float dt) override {};
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override;
	virtual void End() override;

	unsigned int& LoadTexture(std::string name);
	Model* LoadModel(std::string name);
	FMOD::Sound* LoadSound(std::string name, FMOD::System* mAManSystem, FMOD_MODE soundLoadMode = FMOD_DEFAULT);
public:
private:
private:
	/// Base directory
	std::string resourceDirectory;

	/// Loaded textures
	std::string textureDirectory;
	std::unordered_map<std::string, unsigned int> textures;

	/// Loaded models
	std::string modelDirectory;
	std::unordered_map<std::string, Model*> models;

	/// Loaded audio resources
	std::string audioDirectory;
	std::unordered_map<std::string, FMOD::Sound*> audioMusic;
};


#endif

