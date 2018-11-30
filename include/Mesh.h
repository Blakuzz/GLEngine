#pragma once

#include "Texture.h"

#include <vector>
#include <unordered_map>

class Mesh
{
public:
	Mesh();
	bool load(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& colors, std::vector<float>& textureCoordinates);
	void addTexture(unsigned int id, Texture texture);
	void render();
	void destroy();
	~Mesh();
private:
	unsigned int verticesCount = 0;
	unsigned int verticesVBOId = 0;
	unsigned int colorsVBOId = 0;
	unsigned int textureCoordinatesVBOId = 0;
	unsigned int EBOId = 0;
	unsigned int VAOId = 0;

	std::unordered_map<unsigned int, Texture> textures;

};

