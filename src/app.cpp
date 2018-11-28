#include "Engine.h"

void processUserInput(Engine& engine) {
	if (engine.eventHappened(GLFW_KEY_ESCAPE, GLFW_PRESS)) {
		engine.closeWindow();
	}
}

int main(int argc, char** argv) {
	
	Engine engine = Engine(1024, 768);
	if (!engine.init()) {
		return 1;
	}

	while (!engine.windowsWasClosed()) {
		engine.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processUserInput(engine);
		engine.swapBuffer();
	}

	engine.terminate();
	return 0;
}