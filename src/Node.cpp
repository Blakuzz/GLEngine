#include "Node.h"



Node::Node()
{
}

void Node::addChild(Node* node) {
	this->children.push_back(node);
}

void Node::scale(glm::vec3& scaling) {
	this->scaling *= scaling;
}

void Node::rotate(glm::vec3& axis, float degrees) {
	this->rotation = glm::rotate(this->rotation, glm::radians(degrees), axis);
}

void Node::translate(glm::vec3& translation) {
	this->translation += translation;
}

void Node::setScale(glm::vec3& scaling) {
	this->scaling = scaling;
}

void Node::setTranslation(glm::vec3& translation) {
	this->translation = translation;
}

void Node::resetRotation() {
	this->rotation = glm::mat4(1);
}

void Node::updateWorldPosition(glm::mat4& parentTransform) {
	
	glm::mat4 scale = glm::scale(glm::mat4(1), this->scaling);
	glm::mat4 translate = glm::translate(glm::mat4(1), this->translation);
	glm::mat4 transform = translate * this->rotation * scale;
	this->worldPosition = parentTransform * transform;
	
	for (Node* child : this->children) {
		child->updateWorldPosition(this->worldPosition);
	}

}


void Node::render(glm::mat4& cameraProjection, glm::mat4& cameraView) {

	for (Node* child : this->children) {
		child->render(cameraProjection, cameraView);
	}

}

Node::~Node()
{
}