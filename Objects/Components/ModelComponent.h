#pragma once

#ifndef _MCOMP_H_
#define _MCOMP_H_

#include "..//Component.h"


class Model;
class AssetManager;
class GraphicsManager;

class ModelComponent : public Component
{
public:
	ModelComponent();
	virtual ~ModelComponent();

	virtual void Update(float dt) override {};
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override;
	virtual void End() override;

	void Draw();

	void SetModel(std::string nName);
	Model* GetModel() const;

	void PassLoader(AssetManager* nLoader);
	void PassDrawer(GraphicsManager* nDrawer);
public:
private:
private:
	Model* mModel;
	AssetManager* loader;
	GraphicsManager* drawer;
};




#endif




