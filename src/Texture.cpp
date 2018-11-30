#include "Texture.h"

#include "GlStuff.h"

#include <iostream>
Texture::Texture(int width, int height, int channelsCount)
{
	this->width = width;
	this->height = height;
	this->channelsCount = channelsCount;
}

bool Texture::load(std::vector<unsigned char>& data) {

	if (this->textureId > 0) {
		return false;
	}

	glGenTextures(1, &this->textureId);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, this->textureId); // bindo questa a texture0, 0 default
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0); // bindo questa a texture0, 0 default
}

void Texture::destroy() {
	glDeleteTextures(1, &this->textureId);
}

Texture::~Texture()
{
}
