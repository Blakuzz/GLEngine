#pragma once

#include "GlStuff.h"
#include <string>

class Shader
{
public:
	Shader(std::string code, unsigned int shaderType);
	bool compile();
	unsigned int getGLId();
	// delete shader with glId from opengl context;
	void destroy();
	// destructor will be in future used for eventual heap allocation
	~Shader();
private:
	std::string code = "";
	unsigned int glId = 0;
	unsigned int type = 0;
public:
	const static unsigned int VERTEX_SHADER = GL_VERTEX_SHADER;
	const static unsigned int FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
};

