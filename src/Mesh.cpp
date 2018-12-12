#include "Mesh.h"

#include <array>
#include <unordered_map>
#include "GlStuff.h"

Mesh::Mesh(ShaderProgram shaderProgram){
	this->shaderProgram = shaderProgram;
}

bool Mesh::load(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& colors, std::vector<float>& textureCoordinates) {

	if (this->VAOId > 0) {
		return false;
	}

	this->verticesCount = vertices.size();

	glGenVertexArrays(1, &this->VAOId);
	glGenBuffers(1, &this->verticesVBOId);
	glGenBuffers(1, &this->colorsVBOId);
	glGenBuffers(1, &this->textureCoordinatesVBOId);
	glGenBuffers(1, &this->EBOId);

	glBindVertexArray(this->VAOId);

	// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->verticesVBOId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// colors
	glBindBuffer(GL_ARRAY_BUFFER, this->colorsVBOId);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, this->textureCoordinatesVBOId);
	glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(float), textureCoordinates.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Mesh::addTexture(unsigned int id, Texture texture) {
	this->textures.insert({ id, texture });
}

std::array<std::string, 8> shaderLabels = { "texture0","texture1", "texture2", "texture3", "texture4", "texture5", "texture6", "texture7" };

void Mesh::render(glm::mat4& cameraProjection, glm::mat4& cameraView) {
	
	this->shaderProgram.bind();

	this->shaderProgram.setMatrix4("modelViewProjection", cameraProjection * cameraView * this->worldPosition);

	for (std::pair<unsigned int, Texture> tex : this->textures)
	{
		this->shaderProgram.setInteger(shaderLabels[tex.first], tex.first);
		Texture texture = tex.second;
		glActiveTexture(GL_TEXTURE0 + tex.first); // nel caso vogliamo usare più texture col sampler
		texture.bind();
	}

	glBindVertexArray(this->VAOId);
	glDrawElements(GL_TRIANGLES, this->verticesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	Texture::unbind();
	ShaderProgram::unbind();

	Node::render(cameraProjection, cameraView);

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
