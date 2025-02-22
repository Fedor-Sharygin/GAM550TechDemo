#include "pch.h"
#include "Mesh.h"

#include "Shader.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, aiColor3D nColorDiff, float nAlpha, aiColor3D nColorSpec, bool trTextures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	colorDiffuse.r = nColorDiff.r;
	colorDiffuse.g = nColorDiff.g;
	colorDiffuse.b = nColorDiff.b;
	colorDiffuse.a = nAlpha;

	colorSpecular.r = nColorSpec.r;
	colorSpecular.g = nColorSpec.g;
	colorSpecular.b = nColorSpec.b;

	areTexturesUsed = trTextures;

	setupMesh();
}


void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}


void Mesh::Draw(Shader* shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string materialName = "material.";
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
		{
			name = "diffuse";
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular")
		{
			name = "specular";
			number = std::to_string(specularNr++);
		}
		else if (name == "texture_normal")
		{
			name = "normal";
			number = std::to_string(normalNr++);
		}
		else if (name == "texture_height")
		{
			name = "height";
			number = std::to_string(heightNr++);
		}

		glUniform1i(glGetUniformLocation(shader->ID, (materialName + name/* + number*/).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	shader->SetVec4("material.colorDiffuse", colorDiffuse);
	shader->SetVec3("material.colorSpecular", colorSpecular);

	shader->SetBool("textureMaterial", areTexturesUsed);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}