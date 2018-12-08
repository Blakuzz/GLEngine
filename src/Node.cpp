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

Node::~Node()
{
}