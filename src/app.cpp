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

	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VBO, EBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	
	while (!engine.windowsWasClosed()) {
		engine.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processUserInput(engine);

		// in future change shader program
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); solid
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		engine.swapBuffer();
	}

	engine.terminate();
	return 0;
}