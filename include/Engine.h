#pragma once

#include "GlStuff.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"

class Engine
{
public:
	Engine(int width, int height);
	bool init();
	void render(Camera& camera, Node& root);
	void clearColor(float red, float green, float blue, float alpha);
	bool eventHappened(int keyId, int status);
	void swapBuffer();
	void closeWindow();
	bool windowsWasClosed();
	void terminate();
	~Engine();

	static float lastMouseX;
	static float lastMouseY;
	static float yaw;
	static float pitch;
	static bool firstMouse;
private:
	int width = 0;
	int height = 0;
	GLFWwindow* window = NULL;
};
