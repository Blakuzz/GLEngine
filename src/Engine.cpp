#include "Engine.h"

#include <iostream>

Engine::Engine(int width, int height)
{
	this->width = width;
	this->height = height;
}

// callback that update viewport size, when windows is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool Engine::init() {
	// setup OpenGL version and profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window
	this->window = glfwCreateWindow(this->width, this->height, "GLEngine", NULL, NULL);
	if (this->window == NULL) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// pass to glad the glfw function (OS independent) that load OpenGL function adresses
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	// size of the rendering window inside the main window, viewport
	glViewport(0, 0, this->width, this->height);
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);

	return true;
}

bool Engine::setShaderProgram(Shader vertexShader, Shader fragmentShader) {
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader.getGLId());
	glAttachShader(this->shaderProgram, fragmentShader.getGLId());
	glLinkProgram(this->shaderProgram);
	
	int success;
	char infoLog[512];
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		std::cerr << "Error during shader program linking\n" << infoLog << std::endl;
		return false;
	}

	glUseProgram(this->shaderProgram);

	return true;
}


void Engine::clearColor(float red, float green, float blue, float alpha) {
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Engine::eventHappened(int keyId, int status) {
	return glfwGetKey(this->window, keyId) == status;
}

void Engine::swapBuffer() {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void Engine::closeWindow() {
	glfwSetWindowShouldClose(this->window, true);
}

bool Engine::windowsWasClosed() {
	return glfwWindowShouldClose(window);
}

void Engine::terminate() {
	glfwTerminate();
}

Engine::~Engine()
{
}