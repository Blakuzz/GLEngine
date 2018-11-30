#include "Mesh.h"

#include "GlStuff.h"

Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& colors, std::vector<float>& textureCoordinates)
{
	this->vertices = vertices;
	this->indices = indices;
	this->colors = colors;
	this->textureCoordinates = textureCoordinates;

	glGenVertexArrays(1, &this->VAOId);
	glGenBuffers(1, &this->verticesVBOId);
	glGenBuffers(1, &this->colorsVBOId);
	glGenBuffers(1, &this->textureCoordinatesVBOId);
	glGenBuffers(1, &this->EBOId);

	glBindVertexArray(this->VAOId);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->verticesVBOId);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);
		
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	// colors
	glBindBuffer(GL_ARRAY_BUFFER, this->colorsVBOId);
	glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(float), this->colors.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	// texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, this->textureCoordinatesVBOId);
	glBufferData(GL_ARRAY_BUFFER, this->textureCoordinates.size() * sizeof(float), this->textureCoordinates.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

unsigned int Mesh::getVAOId() {
	return this->VAOId;
}

unsigned int Mesh::getVerticesCount() {
	return this->indices.size();
}

void Mesh::destroy() {
	glDeleteVertexArrays(1, &VAOId);
	glDeleteBuffers(1, &verticesVBOId);
	glDeleteBuffers(1, &colorsVBOId);
	glDeleteBuffers(1, &EBOId);
}

Mesh::~Mesh()
{
}
