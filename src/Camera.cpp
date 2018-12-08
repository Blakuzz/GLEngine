#include "Camera.h"



Camera::Camera(glm::mat4& projection)
{
	this->projection = projection;
}

glm::mat4 Camera::getProjection() {
	return this->projection;
}

glm::mat4 Camera::getView() {
	return glm::mat4(1);
}

Camera::~Camera()
{
}
