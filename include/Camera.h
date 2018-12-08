#pragma once

#include "GlStuff.h"
#include "ShaderProgram.h"

class Camera: public Node
{
public:
	Camera(glm::mat4& projection);
	glm::mat4& getProjection();
	~Camera();
private:
	glm::mat4 projection;
};

