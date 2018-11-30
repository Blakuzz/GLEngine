#pragma once
class Texture
{
public:
	Texture();
	void load(unsigned char* data, int width, int height, int channelsCount);
	void bind();
	void unbind();
	void destroy();
	~Texture();
private:
	unsigned int textureId;
};

