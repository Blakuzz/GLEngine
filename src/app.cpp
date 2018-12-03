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

Texture loadTexture(std::string path, bool flip_vertically) {

	stbi_set_flip_vertically_on_load(flip_vertically);
	
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	
	if (data == NULL) {
		stbi_image_free(data);
		std::cerr << "Image file is invalid or not found" << std::endl;
		//throw 1;
	}

	Texture texture = Texture(width, height, nrChannels);
	if (!texture.load(std::vector<unsigned char>(data, data + width * height * nrChannels))) {
		stbi_image_free(data);
		std::cerr << "Error during texture load" << std::endl;
		//throw 1;
	}

	stbi_image_free(data);

	return texture;
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

	vertexShader.destroy();
	fragmentShader.destroy();

	std::vector<float> vertices = {
		-0.5f,  -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f, 
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5, 0.0
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 1, 3
	};
	std::vector<float> colors = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
	};
	std::vector<float> textureCoordinates = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};

	Mesh mesh = Mesh(shaderProgram);
	if (!mesh.load(vertices, indices, colors, textureCoordinates)) {
		std::cerr << "Error during mesh load" << std::endl;
		return 1;
	}

	Texture texture0 = loadTexture("..\\engine\\resources\\textures\\wall.jpg", false);
	Texture texture1 = loadTexture("..\\engine\\resources\\textures\\awesomeface.png", true);

	mesh.addTexture(0, texture0);
	mesh.addTexture(1, texture1);

	float angle = 0;
	float angleInc = 0.1;
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
	glm::vec3 scaleInc = glm::vec3(1.001, 1.001, 1.001);
	glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 translationInc = glm::vec3(0.001,0.001,0.001);
	int times = 0;

	while (!engine.windowsWasClosed()) {
		engine.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processUserInput(engine);

		if (times < 3) {
			if (angle < 0 || angle > 90) {
				angleInc = -angleInc;
				times++;
			}
			angle += angleInc;
			mesh.rotate(glm::vec3(0.0f, 0.0f, 1.0f), angleInc);
		}

		else if (times == 3) {
			if (scale.x > 1.5) {
				times++;
			}
			scale = scale * scaleInc;
			mesh.scale(scaleInc);
		}

		else if (times < 7) {
			if (translation.x < 0 || translation.x > 0.5) {
				translationInc.x = -translationInc.x;
				translationInc.y = -translationInc.y;
				translationInc.z = -translationInc.z;
				times++;
			}
			translation = translation + translationInc;
			mesh.translate(translationInc);
		}
		else if (times < 1000) {
			times++;
		}
		else if (times < 2000) {
			mesh.resetRotation();
			times++;
		}
		else if (times < 3000) {
			mesh.setScale(glm::vec3(1.0f));
			times++;
		}
		else if (times < 4000) {
			mesh.setTranslation(glm::vec3(0.0f));
			times++;
		}

		engine.render(mesh);

		engine.swapBuffer();
	}

	texture0.destroy();
	texture1.destroy();
	mesh.destroy();
	shaderProgram.destroy();
	engine.terminate();

	return 0;
}