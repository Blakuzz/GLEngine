#pragma once

#include "GlStuff.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Camera.h"

#include <vector>
#include <unordered_map>

class Mesh
{
public:
	Mesh(ShaderProgram shaderProgram);
	bool load(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& colors, std::vector<float>& textureCoordinates);
	void scale(glm::vec3& scaling);
	void rotate(glm::vec3& axis, float degrees);
	void translate(glm::vec3& translation); 
	void setScale(glm::vec3& scaling);
	void setTranslation(glm::vec3& translation);
	void resetRotation();
	void addTexture(unsigned int id, Texture texture);
	void render(Camera& camera);
	void destroy();
	~Mesh();
private:
	ShaderProgram shaderProgram;
	unsigned int verticesCount = 0;
	unsigned int verticesVBOId = 0;
	unsigned int colorsVBOId = 0;
	unsigned int textureCoordinatesVBOId = 0;
	unsigned int EBOId = 0;
	unsigned int VAOId = 0;
	std::unordered_map<unsigned int, Texture> textures;
	glm::vec3 scaling = glm::vec3(1);
	glm::mat4 rotation = glm::mat4(1);
	glm::vec3 translation = glm::vec3(0);
};

