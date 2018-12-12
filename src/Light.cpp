#include "Light.h"



Light::Light(ShaderProgram shaderProgram, glm::vec3 color)
{
	this->shaderProgram = shaderProgram;
	this->color = color;
}

void Light::render(glm::mat4& cameraProjection, glm::mat4& cameraView) {
	this->shaderProgram.bind();
	this->shaderProgram.setVec3("lightColor", this->color);
	ShaderProgram::unbind();
}

Light::~Light()
{
}
