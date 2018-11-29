#include "ShaderProgram.h"

#include "GlStuff.h"
#include <iostream>

ShaderProgram::ShaderProgram()
{
	this->glId = glCreateProgram();
}

bool ShaderProgram::link(Shader vertexShader, Shader fragmentShader) {
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

unsigned int ShaderProgram::getGLId() {
	return this->glId;
}

void ShaderProgram::destroy() {
	glDeleteProgram(this->glId);
}


ShaderProgram::~ShaderProgram()
{
}
