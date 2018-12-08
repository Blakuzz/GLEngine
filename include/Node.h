#pragma once

#include "GlStuff.h"
#include "Node.h"
#include <vector>

class Node
{
public:
	Node();
	void addChild(Node* node);
	void scale(glm::vec3& scaling);
	void rotate(glm::vec3& axis, float degrees);
	void translate(glm::vec3& translation);
	void setScale(glm::vec3& scaling);
	void setTranslation(glm::vec3& translation);
	void resetRotation();
	void updateWorldPosition(glm::mat4& parentTransform = glm::mat4(1));
	virtual void render(glm::mat4& cameraProjection, glm::mat4& cameraView);
	~Node();
protected:
	glm::vec3 scaling = glm::vec3(1);
	glm::mat4 rotation = glm::mat4(1);
	glm::vec3 translation = glm::vec3(0);
	glm::mat4 worldPosition = glm::mat4(1);
private:
	std::vector<Node*> children;
};

