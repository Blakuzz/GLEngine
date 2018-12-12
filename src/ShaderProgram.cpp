#include "ShaderProgram.h"

#include "GlStuff.h"
#include <iostream>

ShaderProgram::ShaderProgram(){}

bool ShaderProgram::link(Shader vertexShader, Shader fragmentShader) {
	
	if (this->glId > 0) {
		return false;
	}

	this->glId = glCreateProgram();
	glAttachShader(this->glId, vertexShader.getGLId());
	glAttachShader(this->glId, fragmentShader.getGLId());
	glLinkProgram(this->glId);

	int success;
	char infoLog[512];
	glGetProgramiv(this->glId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->glId, 512, NULL, infoLog);
		std::cerr << "Error during shader program linking\n" << infoLog << std::endl;
		return false;
	}

	glUseProgram(this->glId);

	return true;
}

void ShaderProgram::bind() {
	glUseProgram(this->glId);
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

void ShaderProgram::setMatrix4(const std::string &name, const glm::mat4 &matrix) {
	glUniformMatrix4fv(glGetUniformLocation(this->glId, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::setInteger(const std::string &name, int value) {
	glUniform1i(glGetUniformLocation(this->glId, name.c_str()), value);
}


void ShaderProgram::setVec3(const std::string &name, glm::vec3& vector) {
	glUniform3fv(glGetUniformLocation(this->glId, name.c_str()), 1, &vector[0]);
}

void ShaderProgram::destroy() {
	glDeleteProgram(this->glId);
}


ShaderProgram::~ShaderProgram()
{
}
