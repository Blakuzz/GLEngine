#pragma once

#include <vector>

class Texture
{
public:
	Texture(std::vector<unsigned char>& data, int width, int height, int channelsCount);
	bool load();
	void bind();
	void unbind();
	void destroy();
	~Texture();
private:
	std::vector<unsigned char> data;
	int width = 0;
	int height = 0;
	int channelsCount = 0;
	unsigned int textureId = 0;
};

