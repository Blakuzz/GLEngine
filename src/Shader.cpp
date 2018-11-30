#include "Shader.h"

#include <iostream>

Shader::Shader(std::string code, unsigned int shaderType)
{
	this->code = code;
	this->type = shaderType;
}

bool Shader::compile() {

	if (this->glId > 0) {
		return false;
	}

	this->glId = glCreateShader(this->type);
	const char *vertex_file_c_str = this->code.c_str();
	glShaderSource(this->glId, 1, &vertex_file_c_str, NULL);
	glCompileShader(this->glId);

	int success;
	char infoLog[512];
	glGetShaderiv(this->glId, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(this->glId, 512, NULL, infoLog);
		std::cerr << "Error during shader compilation\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

unsigned int Shader::getGLId() {
	return this->glId;
}

void Shader::destroy() {
	glDeleteShader(this->glId);
}

Shader::~Shader()
{

}
