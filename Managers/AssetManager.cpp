#include "pch.h"
#include "AssetManager.h"

#include "..//Graphics//Model.h"


AssetManager::AssetManager()
	:
	Manager(MANAGER_TYPE::TYPE_ASSET_MANAGER)
{}


void AssetManager::Initialize()
{
	resourceDirectory = "Resources/";

	textureDirectory = "Textures/";
    modelDirectory = "Models/";
	audioDirectory = "Audio/";

    textures = std::unordered_map<std::string, unsigned int>();
    models = std::unordered_map<std::string, Model*>();
    audioMusic = std::unordered_map<std::string, FMOD::Sound*>();
}


void AssetManager::End()
{
    
}


unsigned int& AssetManager::LoadTexture(std::string name)
{
	unsigned int* textureRet;

    /// the texture was not found => load it
	if (textures.end() == textures.find(name))
	{
        unsigned int textVal;

        std::string fullPath = resourceDirectory + textureDirectory + name;

        glGenTextures(1, &textVal);
        glBindTexture(GL_TEXTURE_2D, textVal);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
        if (nullptr != data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        textures[name] = textVal;
	}

	/// if the texture name already exists in map => return it
	/// the texture was already loaded
	textureRet = &textures[name];

    /// Return the found/loaded texture
    return *textureRet;
}


Model* AssetManager::LoadModel(std::string name)
{
    /// if we haven't found the loaded name
    /// load and return it
    if (models.end() == models.find(name))
    {
        std::string fullPath = resourceDirectory + modelDirectory + name;
        Model* newModel = new Model(fullPath);
        models[name] = newModel;
        return newModel;
    }

    /// otherwise, return the loaded model
    return models[name];
}


FMOD::Sound* AssetManager::LoadSound(std::string name, FMOD::System* mAManSystem, FMOD_MODE soundLoadMode)
{
    /// if we haven't found the loaded name
    /// load and return it
    if (audioMusic.end() == audioMusic.find(name))
    {
        std::string fullPath = resourceDirectory + audioDirectory + name;
        FMOD::Sound* newSound = nullptr;
        FMOD_RESULT result = mAManSystem->createSound(fullPath.c_str(), soundLoadMode, nullptr, &newSound);
        if (FMOD_OK != result)
        {
            std::cerr << "FMOD Error! " << result << " " << FMOD_ErrorString(result) << std::endl;
            exit(-1);
        }

        audioMusic[name] = newSound;
        return newSound;
    }

    /// otherwise, return the loaded sound
    return audioMusic[name];
}

