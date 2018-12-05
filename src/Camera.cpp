#include "Camera.h"



Camera::Camera(glm::mat4& projection)
{
	this->projection = projection;
}

glm::mat4& Camera::getProjection() {
	return this->projection;
}

Camera::~Camera()
{
}
