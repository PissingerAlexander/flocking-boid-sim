#include "headers/renderer.h"

Renderer::Renderer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Renderer::init(float width, float height) {
	projectionMatrix = calculateProjectionMatrix(width, height);
	viewMatrix = Matrix4();
}

void Renderer::render(const std::vector<Boid>& boids) {
	for(const Boid& boid : boids) {
		Matrix4 model = createModelMatrix(boid.position, boid.rotation);
		// Matrix4 mvp = projection * view * model;
		//  or, send projection, view and model as uniform and multiply them there
		// Send to gpu and render here, or collect vertex data and indices and send below
		std::cout << boid.position.x << std::endl;
		std::cout << model[3] << std::endl;
	}

	// If vertex data and indices collected: Send to gpu and render
}

Matrix4 Renderer::calculateProjectionMatrix(float width, float height) {
	return Matrix4(	1/width, 0, 0, 0,
			0, 1/height, 0, 0,
			0, 0, -(2/(5-1)), 0,
			0, 0, -((5+1)/(5-1)), 1);
}

Matrix4 Renderer::createModelMatrix(Vector2 position, float rotation) {
	// Matrix4 rotationMatrix = Matrix4(	cos(rotation), sin(rotation), 0, 0,
	// 					-sin(rotation), cos(rotation), 0, 0,
	// 					0, 0, 1, 0,
	// 					0, 0, 0, 1);
	Matrix4 rotationMatrix = Matrix4();
	Matrix4 translationMatrix = Matrix4(	1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						position.x, position.y, 1, 1);
	return translationMatrix * rotationMatrix;
}
