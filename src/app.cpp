#include "Engine.h"
#include "Shader.h"
#include "Texture.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
	if (!shaderProgram.link(vertexShader, fragmentShader)) {
		std::cerr << "Shader program can not be linked" << std::endl;
		return 1;
	}

	engine.setShaderProgram(shaderProgram);

	vertexShader.destroy();
	fragmentShader.destroy();

	std::vector<float> vertices = {
		-0.5f,  -0.5f, 0.0f,  // left bottom
		0.5f, -0.5f, 0.0f,  // right bottom
		0.0f, 0.5f, 0.0f,  // central top
	};
	std::vector<unsigned int> indices = {  // note that we start from 0!
		0, 1, 2   // first triangle
	};
	std::vector<float> colors = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};
	std::vector<float> textureCoordinates = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};

	Mesh mesh = Mesh();
	if (!mesh.load(vertices, indices, colors, textureCoordinates)) {
		std::cerr << "Error during mesh load" << std::endl;
		return 1;
	}

	int width, height, nrChannels;
	unsigned char *data = stbi_load("..\\engine\\resources\\textures\\wall.jpg", &width, &height, &nrChannels, 0);

	if (data == NULL) {
		std::cerr << "Image file is invalid or not found" << std::endl;
		return 1;
	}

	Texture texture = Texture(width, height, nrChannels);
	
	if (!texture.load(std::vector<unsigned char>(data, data + width * height * nrChannels))) {
		stbi_image_free(data);
		std::cerr << "Error during texture load" << std::endl;
		return 1;
	}

	

	while (!engine.windowsWasClosed()) {
		engine.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processUserInput(engine);

		glActiveTexture(GL_TEXTURE0); // nel caso vogliamo usare più texture col sampler
		texture.bind();
		engine.render(mesh);
		texture.unbind();

		engine.swapBuffer();
	}

	texture.destroy();
	mesh.destroy();
	shaderProgram.destroy();
	engine.terminate();
	return 0;
}