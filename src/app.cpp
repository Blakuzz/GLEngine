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

void updateCamera(Engine& engine, Camera& camera, float elapsedTime) {
	float speed = 2.5f;
	float movement = speed * elapsedTime;
	glm::vec3 position = camera.getPosition();
	glm::vec3 target = camera.getDirection();
	glm::vec3 up = camera.getUp();
	if (engine.eventHappened(GLFW_KEY_W, GLFW_PRESS))
		camera.setPosition(position + movement * target);
	if (engine.eventHappened(GLFW_KEY_S, GLFW_PRESS))
		camera.setPosition(position - movement * target);
	if (engine.eventHappened(GLFW_KEY_A, GLFW_PRESS))
		camera.setPosition(position - movement * glm::normalize(glm::cross(target, up)));	
	if (engine.eventHappened(GLFW_KEY_D, GLFW_PRESS))
		camera.setPosition(position + movement * glm::normalize(glm::cross(target, up)));

	float yaw = Engine::yaw;
	float pitch = Engine::pitch;

	camera.setDirection(glm::normalize(glm::vec3(
		cos(glm::radians(pitch)) * sin(glm::radians(yaw)),
		- sin(glm::radians(pitch)),
		- cos(glm::radians(pitch)) * cos(glm::radians(yaw))
		)));

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

	int width = 1024;
	int height = 768;

	Engine engine = Engine(width, height);
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
		0.5f, 0.5f, 0.0f
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

	Node root; 
	
	Mesh cube[6] = { Mesh(shaderProgram), Mesh(shaderProgram), Mesh(shaderProgram), Mesh(shaderProgram), Mesh(shaderProgram), Mesh(shaderProgram) };

	cube[0].translate(glm::vec3(0.0f, 0.0f, 0.5f));
	cube[1].translate(glm::vec3(0.5f, 0.0f, 0.0f));
	cube[1].rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90);
	cube[2].translate(glm::vec3(0.0f, 0.0f, -0.5f));
	cube[2].rotate(glm::vec3(0.0f, 1.0f, 0.0f), 180);
	cube[3].translate(glm::vec3(-0.5f, 0.0f, 0.0f));
	cube[3].rotate(glm::vec3(0.0f, 1.0f, 0.0f), 270);
	cube[4].translate(glm::vec3(0.0f, 0.5f, 0.0f));
	cube[4].rotate(glm::vec3(1.0f, 0.0f, 0.0f), 90);
	cube[5].translate(glm::vec3(0.0f, -0.5f, 0.0f));
	cube[5].rotate(glm::vec3(1.0f, 0.0f, 0.0f), -90);

	Texture texture0 = loadTexture("..\\engine\\resources\\textures\\wall.jpg", false);
	Texture texture1 = loadTexture("..\\engine\\resources\\textures\\awesomeface.png", true);

	for (int i = 0; i < 6; i++) {
		if (!cube[i].load(vertices, indices, colors, textureCoordinates)) {
			std::cerr << "Error during mesh load" << std::endl;
			return 1;
		}
		cube[i].addTexture(0, texture0);
		cube[i].addTexture(1, texture1);
	
		root.addChild(&cube[i]);
	}

	root.translate(glm::vec3(0.0f, 0.0f, -5.0f));

	Camera camera = Camera(glm::perspective(glm::radians(45.0f), width / float(height), 0.1f, 100.0f));

	float angleInc = 0.01;

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!engine.windowsWasClosed()) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		engine.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processUserInput(engine);
		updateCamera(engine, camera, deltaTime);

		root.rotate(glm::vec3(0.33f, 0.33f, 0.33f), angleInc);

		engine.render(camera, root);

		engine.swapBuffer();
	}

	texture0.destroy();
	texture1.destroy();
	for (int i = 0; i < 6; i++) {
		cube[i].destroy();
	}
	shaderProgram.destroy();
	engine.terminate();

	return 0;
}