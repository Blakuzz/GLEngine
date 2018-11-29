#pragma once

#include <vector>

class Mesh
{
public:
	Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& colors);
	unsigned int getVAOId();
	unsigned int getVerticesCount();
	void destroy();
	~Mesh();
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> colors;
	unsigned int verticesVBOId;
	unsigned int colorsVBOId;
	unsigned int EBOId;
	unsigned int VAOId;
};

