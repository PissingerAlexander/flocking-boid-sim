#pragma once

#include <iostream>
#include <vector>

#include "matrix4.h"
#include "shader.h"
#include "boid.h"

class Renderer {
	Matrix4 view;
	Matrix4 projection;

	Shader *shader;

	unsigned int VAO, VBO, EBO;

	Renderer(GLFWwindow *window);
	~Renderer();

	void init();
	void render(const std::vector<Boid>& boids);
};
