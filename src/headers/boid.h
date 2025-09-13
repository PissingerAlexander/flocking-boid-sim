#pragma once

#include <iostream>

#include <vector>
#include <cstdlib>
#include <cmath>

#include "constants.h"
#include "vector2.h"

class Boid {
	public:
		unsigned int id;
		Vector2 velocity;
		Vector2 position;

		Boid(unsigned int id);
		Boid(unsigned int id, float x, float y);
		~Boid();

		void update(const float delta, const std::vector<Boid>& boids);
	private:
		void applySteer(const std::vector<Boid>& boids);
};
