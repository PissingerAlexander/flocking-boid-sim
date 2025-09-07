#include "headers/program.h"

Program::Program() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialise GLFW" << std::endl;
		return;
	}
}

Program::~Program() {
	destroy();
}

void Program::destroy() {
	running = false;

	if (windowSetup) {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	windowSetup = false;
}

void Program::initWindow(const char *title, int width, int height) {
	if (windowSetup) {
		std::cout << "Window already created" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Program::FramebufferSizeCallback);

	if (!gladLoadGL(glfwGetProcAddress)) {
		std::cerr << "Failed to initialise GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, width, height);

	windowSetup = true;
}

void Program::run() {
	if (!windowSetup) {
		std::cerr << "No window setup" << std::endl;
		return;
	}

	running = true;
	while (running) {
		if (glfwWindowShouldClose(window)) {
			running = false;
			break;
		}
		
		// outsource in input handler?
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
		// clear screen
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Program::getFramebufferSize(int *width, int *height) {
	glfwGetFramebufferSize(window, width, height);
}

void Program::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}
