#include "headers/renderer.h"

void Renderer::render(const std::vector<Boid>& boids) {
	for(const Boid& boid : boids) {
		Matrix4 model = Matrix4(); // createModelMatrix(boid.position, boid.rotation);
		// Matrix4 mvp = projection * view * model;
		// Send to gpu and render
		std::cout << boid.position.x << std::endl;
		std::cout << model[3] << std::endl;
	}
}
