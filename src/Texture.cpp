#include "Texture.h"

#include "GlStuff.h"

Texture::Texture()
{
	glGenTextures(1, &this->textureId);

}

void Texture::load(unsigned char* data, int width, int height, int channelsCount) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
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
