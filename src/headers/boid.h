#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>

#include "vector2.h"

#define MAX_VELOCITY 2

class Boid {
	public:
		Vector2 position;
		Vector2 velocity;
		float rotation;

		Boid(float x, float y, float rotation): position(x, y), rotation(rotation) {};
		~Boid();

		void update(const float delta, std::vector<Boid*> boids);
};
