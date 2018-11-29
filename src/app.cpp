#include "Engine.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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

	Shader vertexShader = Shader(vertexShaderCode, Shader::VERTEX_SHADER);
	Shader fragmentShader = Shader(fragmentShaderCode, Shader::FRAGMENT_SHADER);

	if (!vertexShader.compile()) {
		engine.terminate();
		return 1;
	}
	
	if (!fragmentShader.compile()) {
		engine.terminate();
		return 1;
	}

	ShaderProgram shaderProgram = ShaderProgram();
	shaderProgram.link(vertexShader, fragmentShader);

	engine.setShaderProgram(shaderProgram);

	vertexShader.destroy();
	fragmentShader.destroy();

	std::vector<float> vertices = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	std::vector<unsigned int> indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	std::vector<float> colors = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f
	};

	Mesh mesh = Mesh(vertices, indices, colors);
	
	while (!engine.windowsWasClosed()) {
		engine.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processUserInput(engine);

		engine.render(mesh);

		engine.swapBuffer();
	}

	mesh.destroy();
	shaderProgram.destroy();
	engine.terminate();
	return 0;
}