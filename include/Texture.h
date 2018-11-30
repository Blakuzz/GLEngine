#pragma once

#include <vector>

class Texture
{
public:
	Texture(int width, int height, int channelsCount);
	bool load(std::vector<unsigned char>& data);
	void bind();
	static void unbind();
	void destroy();
	~Texture();
private:
	int width = 0;
	int height = 0;
	int channelsCount = 0;
	unsigned int textureId = 0;
};

