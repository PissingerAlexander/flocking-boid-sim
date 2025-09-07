#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>

#include "vector2.h"

class Boid {
	public:
		Vector2 position;
		Vector2 velocity;

		Boid(float x, float y): position(x, y) {};
		~Boid();

		void update(const float delta, std::vector<Boid*> boids);
		void render(unsigned int VAO, unsigned int VBO, unsigned int EBO);
};
