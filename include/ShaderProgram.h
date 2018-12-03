#pragma once

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	bool link(Shader vertexShader, Shader fragmentShader);
	void bind();
	static void unbind();
	// call after glUseProgram
	void ShaderProgram::setMatrix4(const std::string &name, const glm::mat4 &matrix);
	// call after glUseProgram
	void ShaderProgram::setInteger(const std::string &name, int value);
	void destroy();
	~ShaderProgram();
private:
	unsigned int glId = 0;
};

