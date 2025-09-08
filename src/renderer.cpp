#include "headers/renderer.h"

Renderer::Renderer(GLFWwindow *window) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Renderer::~Renderer() {

}

void Renderer::init() {
	
}

void Renderer::render(const std::vector<Boid>& boids) {
	for(const Boid& boid : boids) {
		Matrix4 model = Matrix4(); // createModelMatrix(boid.position, boid.rotation);
		// Matrix4 mvp = projection * view * model;
		// Send to gpu and render here, or collect vertex data and indices and send below
		std::cout << boid.position.x << std::endl;
		std::cout << model[3] << std::endl;
	}

	// If vertex data and indices collected: Send to gpu and render
}
