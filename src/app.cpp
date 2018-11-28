#include "Engine.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <iostream>

// glfw now debug lib!

void processUserInput(Engine& engine) {
	if (engine.eventHappened(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
		engine.closeWindow();
	}
}

std::string readFile(std::string path) {
	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
}

int main(int argc, char** argv) {
	
	std::string vertexShaderCode = readFile("..\\engine\\glsl\\vertex.glsl");
	std::string fragmentShaderCode = readFile("..\\engine\\glsl\\fragment.glsl");
	
	if (vertexShaderCode.size() == 0) {
		std::cerr << "Vertex shader file is empty or path is wrong" << std::endl;
		return 1;
	}

	if (fragmentShaderCode.size() == 0) {
		std::cerr << "Fragment shader file is empty or path is wrong" << std::endl;
		return 1;
	}
	

	Engine engine = Engine(1024, 768);
	if (!engine.init()) {
		return 1;
	}

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	Shader vertexShader = Shader(vertexShaderCode);
	Shader fragmentShader = Shader(fragmentShaderCode);

	if (!vertexShader.compile(Shader::VERTEX_SHADER)) {
		engine.terminate();
		return 1;
	}
	
	if (!fragmentShader.compile(Shader::FRAGMENT_SHADER)) {
		engine.terminate();
		return 1;
	}

	if (!engine.setShaderProgram(vertexShader, fragmentShader)) {
		engine.terminate();
		return 1;
	}

	vertexShader.destroy();
	fragmentShader.destroy();

	while (!engine.windowsWasClosed()) {
		engine.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processUserInput(engine);
		engine.swapBuffer();
	}

	engine.terminate();
	return 0;
}