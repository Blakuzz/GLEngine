#include "Engine.h"

#include <iostream>

float Engine::lastMouseX = 0;
float Engine::lastMouseY = 0;
float Engine::yaw = 0;
float Engine::pitch = 0;
bool Engine::firstMouse = true;

Engine::Engine(int width, int height)
{
	this->width = width;
	this->height = height;
	Engine::lastMouseX = this->width / 2;
	Engine::lastMouseY = this->height / 2;
	Engine::firstMouse = true;
}

// callback that update viewport size, when windows is resized
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	
	if (Engine::firstMouse) {
		Engine::lastMouseX = xPos;
		Engine::lastMouseY = yPos;
		Engine::firstMouse = false;
	}

	float xOffset = xPos - Engine::lastMouseX;
	float yOffset = yPos - Engine::lastMouseY;
	
	Engine::lastMouseX = xPos;
	Engine::lastMouseY = yPos;

	float sensitivity = 0.25f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	Engine::yaw += xOffset;

	Engine::yaw = glm::mod(Engine::yaw, 360.0f);

	Engine::pitch += yOffset;

	if (Engine::pitch > 89.0f)
		Engine::pitch = 89.0f;
	if (Engine::pitch < -89.0f)
		Engine::pitch = -89.0f;
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
	glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);

	// mouse support
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(this->window, mouseCallback);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Engine::render(Camera& camera, Node& root) {
	root.updateWorldPosition();
	root.render(camera.getProjection(), camera.getView());
}

void Engine::clearColor(float red, float green, float blue, float alpha) {
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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