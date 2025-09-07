#pragma once

#include <iostream>
#include <vector>

#include "matrix4.h"
#include "boid.h"

class Renderer {
	Matrix4 view;
	Matrix4 projection;

	void render(const std::vector<Boid>& boids);
};
