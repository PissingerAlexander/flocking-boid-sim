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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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

	std::vector<Boid> boids;

	initBoids(boids);

	Renderer renderer = Renderer();
	renderer.init(WIDTH, HEIGHT);
	renderer.render(window, boids);
}

void Program::initBoids(std::vector<Boid>& boids) {
	for (int i = 0; i < NUM_BOIDS; i++) {
		boids.push_back(Boid(i));
	}
}

void Program::FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}
