#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine
{
public:
	Engine(int width, int height);
	bool init();
	void clearColor(float red, float green, float blue, float alpha);
	bool eventHappened(int keyId, int status);
	void swapBuffer();
	void closeWindow();
	bool windowsWasClosed();
	void terminate();
	~Engine();
private:
	int width;
	int height;
	GLFWwindow* window = NULL;
};
