#pragma once

#include "GlStuff.h"
#include "ShaderProgram.h"

class Camera
{
public:
	Camera(glm::mat4& projection);
	void setUp(glm::vec3& up);
	void setPosition(glm::vec3& position);
	void setDirection(glm::vec3& vector);
	glm::vec3 getUp();
	glm::vec3 getPosition();
	glm::vec3 getDirection();
	glm::mat4 getProjection();
	glm::mat4 getView();
	~Camera();
private:
	glm::mat4 projection = glm::mat4(1);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
};

