#pragma once

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	bool link(Shader vertexShader, Shader fragmentShader);
	unsigned int getGLId(); 
	void destroy();
	~ShaderProgram();
private:
	unsigned int glId = 0;
};

