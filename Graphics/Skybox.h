#pragma once


#ifndef _SKYBOX_H_
#define _SKYBOX_H_


class GraphicsManager;
class AssetManager;

class Skybox
{
public:
	Skybox(std::vector<std::string> nTextures);
	~Skybox();

	void Draw();
	
	void PassDrawer(GraphicsManager* nDrawer);
	void PassLoader(AssetManager* nLoader);

	void LoadFaces();
public:
private:
private:
	static float sbVerts[3 * 6 * 6];
	unsigned int sbVAO, sbVBO;
	std::vector<std::string> sbFaceTextures;
	unsigned int sbTextures;


	GraphicsManager* drawer;
	AssetManager* loader;
};



#endif

