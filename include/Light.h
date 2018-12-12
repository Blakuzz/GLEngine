#pragma once

#include "ShaderProgram.h"
#include "Node.h"

class Light: public Node
{
public:
	Light(ShaderProgram shaderProgram, glm::vec3 color);
	void render(glm::mat4& cameraProjection, glm::mat4& cameraView);
	~Light();
private:
	ShaderProgram shaderProgram; 
	glm::vec3 color;
};

