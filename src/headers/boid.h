#pragma once

#include <iostream>

#include <vector>
#include <cstdlib>
#include <cmath>

#include "constants.h"
#include "vector2.h"

#define MAX_VELOCITY 2

class Boid {
	public:
		unsigned int id;
		Vector2 position;
		Vector2 velocity;

		Boid(unsigned int id);
		Boid(unsigned int id, float x, float y): id(id), position(x, y) {};
		~Boid();

		void update(const float delta, const std::vector<Boid>& boids);
};
