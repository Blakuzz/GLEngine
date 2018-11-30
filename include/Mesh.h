#pragma once

#include <vector>

class Mesh
{
public:
	Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& colors, std::vector<float>& textureCoordinates);
	bool load();
	unsigned int getVAOId();
	unsigned int getVerticesCount();
	void destroy();
	~Mesh();
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> colors;
	std::vector<float> textureCoordinates;
	unsigned int verticesVBOId = 0;
	unsigned int colorsVBOId = 0;
	unsigned int textureCoordinatesVBOId = 0;
	unsigned int EBOId = 0;
	unsigned int VAOId = 0;
};

