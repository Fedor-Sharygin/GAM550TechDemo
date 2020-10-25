#include "pch.h"
#include "ModelComponent.h"

#include "Transform.h"

#include "..//GameObject.h"

#include "..//..//Graphics//Model.h"
#include "..//..//Graphics//Shader.h"

#include "..//..//Managers//Managers.h"


ModelComponent::ModelComponent()
	:
	Component(COMPONENT_TYPE::TYPE_MODEL)
{
	Initialize();
}

ModelComponent::~ModelComponent()
{
	End();
}



void ModelComponent::Initialize()
{
	mModel = nullptr;
	loader = nullptr;
}

void ModelComponent::End()
{}


void ModelComponent::Draw()
{
	Transform* goTr = static_cast<Transform*>(owner->GetComponent<Transform>());

	Shader* mShader = drawer->baseShader;

	/// set the base matrix
	glm::mat4 model = glm::mat4(1.0f);

	/// put it on another position
	glm::vec3 position = goTr->GetPosition();
	model = glm::translate(model, position);

	/// rotate it
	/// x - yaw
	/// y - pitch
	/// z - roll
	glm::vec3 rotation = goTr->GetRotation();
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	/// scale the object
	glm::vec3 scale = goTr->GetScale();
	model = glm::scale(model, scale);

	int loc = glGetUniformLocation(mShader->ID, "model");
	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(model));

	mModel->Draw(mShader);
}


void ModelComponent::SetModel(std::string nName)
{
	mModel = loader->LoadModel(nName);
	if (nullptr == mModel)
	{
		std::cerr << "Error loading model!" << std::endl;
		exit(-1);
	}
}

Model* ModelComponent::GetModel() const
{
	return mModel;
}


void ModelComponent::PassLoader(AssetManager* nLoader)
{
	loader = nLoader;
}

void ModelComponent::PassDrawer(GraphicsManager* nDrawer)
{
	drawer = nDrawer;
}



