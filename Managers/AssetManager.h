#pragma once

#ifndef _ASSET_H_
#define _ASSET_H_

#include "Manager.h"


class AssetManager : public Manager
{
public:
	AssetManager();
	~AssetManager() = default;

	virtual void Update(float dt) override {};
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override {};

	unsigned int LoadTexture(std::string name);
public:
private:
private:
	/// Base directory
	std::string resourceDirectory;

	/// Loaded textures
	std::string textureDirectory;
	std::unordered_map<std::string, unsigned int> textures;

	/// Loaded audio resources
	std::string audioDirectory;
};


#endif

