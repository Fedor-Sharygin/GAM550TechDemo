#include "pch.h"
#include "Skybox.h"

#include "..//Managers//Managers.h"

float Skybox::sbVerts[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};


Skybox::Skybox(std::vector<std::string> nTextures)
{
    sbFaceTextures = nTextures;

    glGenVertexArrays(1, &sbVAO);
    glGenBuffers(1, &sbVBO);
    glBindVertexArray(sbVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sbVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sbVerts), &sbVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

Skybox::~Skybox()
{
    glDeleteVertexArrays(1, &sbVAO);
    glDeleteBuffers(1, &sbVAO);
}


void Skybox::Draw()
{
	Shader* mSBShader = drawer->sbShader;
    glBindVertexArray(sbVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, sbTextures);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}



void Skybox::PassDrawer(GraphicsManager* nDrawer)
{
	drawer = nDrawer;
}

void Skybox::PassLoader(AssetManager* nLoader)
{
    loader = nLoader;
}



void Skybox::LoadFaces()
{
    sbTextures = loader->LoadSkyboxTextures("skybox0", sbFaceTextures);
}

