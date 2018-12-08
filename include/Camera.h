#pragma once

#include "GlStuff.h"
#include "ShaderProgram.h"
#include "Node.h"

class Camera: public Node
{
public:
	Camera(glm::mat4& projection);
	glm::mat4 getProjection();
	glm::mat4 getView();
	~Camera();
private:
	glm::mat4 projection;
};

