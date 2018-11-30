#include "Engine.h"
#include "Shader.h"

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
	shaderProgram.link(vertexShader, fragmentShader);

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

	Mesh mesh = Mesh(vertices, indices, colors, textureCoordinates);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("..\\engine\\resources\\textures\\wall.jpg", &width, &height, &nrChannels, 0);

	if (data == NULL) {
		std::cerr << "Texture file is invalid or not found" << std::endl;
		return 1;
	}

	std::cout << nrChannels << std::endl;

	unsigned int texture;
	glGenTextures(1, &texture);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	// sto configurando l'oggetto assegnato al target gl_texture_2d
	// sto settando solo il primo livello per le mipmap
	// come deve salvare la texture OpenGL
	// dimensioni dell'immagine
	// sempre 0
	// formato e tipo di dato dell'immagine d'origine
	// dati
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	// ora ho la texture bindata all'oggetto, e dico di generare le mipmap (finora avevo settato solo il livello 0)
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	while (!engine.windowsWasClosed()) {
		engine.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processUserInput(engine);

		glBindTexture(GL_TEXTURE_2D, texture);
		engine.render(mesh);

		engine.swapBuffer();
	}

	mesh.destroy();
	shaderProgram.destroy();
	engine.terminate();
	return 0;
}