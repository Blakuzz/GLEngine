#pragma once

#include "GlStuff.h"
#include "Shader.h"
#include "ShaderProgram.h"

class Engine
{
public:
	Engine(int width, int height);
	bool init();
	void setShaderProgram(ShaderProgram shaderProgram);
	void clearColor(float red, float green, float blue, float alpha);
	bool eventHappened(int keyId, int status);
	void swapBuffer();
	void closeWindow();
	bool windowsWasClosed();
	void terminate();
	~Engine();
private:
	int width = 0;
	int height = 0;
	GLFWwindow* window = NULL;
};
