/*	*
	*  License - learnopengl.com mesh.h tutorial
	*/

#pragma once

#ifndef MESH_H
#define MESH_H



class Shader;


struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	/*  Functions  */
	// constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, aiColor3D nColorDiff, float nAlpha, aiColor3D nColorSpec, bool trTextures);

	// render the mesh
	void Draw(Shader* shader);
public:
	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	glm::vec4 colorDiffuse;
	glm::vec3 colorSpecular;
	bool areTexturesUsed;
	unsigned int VAO;
private:
	/*  Functions    */
	// initializes all the buffer objects/arrays
	void setupMesh();
private:
	/*  Render data  */
	unsigned int VBO, EBO;
};
#endif



