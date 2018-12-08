#pragma once

#include "GlStuff.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Node.h"

#include <vector>
#include <unordered_map>

class Mesh: public Node
{
public:
	Mesh(ShaderProgram shaderProgram);
	bool load(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& colors, std::vector<float>& textureCoordinates);
	void addTexture(unsigned int id, Texture texture);
	void render(glm::mat4& cameraProjection, glm::mat4& cameraView);
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
};

