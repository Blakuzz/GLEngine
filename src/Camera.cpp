#include "Camera.h"


Camera::Camera(glm::mat4& projection)
{
	this->projection = projection;
}

void Camera::setUp(glm::vec3& up) {
	this->up = up;
}

void Camera::setPosition(glm::vec3& position) {
	this->position = position;
}

void Camera::setDirection(glm::vec3& vector) {
	this->direction = vector;
}

glm::vec3 Camera::getUp() {
	return this->up;
}

glm::vec3 Camera::getPosition() {
	return this->position;
}

glm::vec3 Camera::getDirection() {
	return this->direction;
}

glm::mat4 Camera::getProjection() {
	return this->projection;
}

glm::mat4 Camera::getView() {
	return glm::lookAt(this->position, this->position + this->direction, this->up);
}

Camera::~Camera()
{
}
