#include "pch.h"
#include "AssetManager.h"


AssetManager::AssetManager()
	:
	Manager(MANAGER_TYPE::TYPE_ASSET_MANAGER)
{}


void AssetManager::Initialize()
{
	resourceDirectory = "Resources/";
	textureDirectory = "Textures/";
	audioDirectory = "Audio/";
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

        bool png = std::string::npos != name.find(".png", name.length() - 5);

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
            if (true == png)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            else if (false == png)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);
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

