#pragma once

#include <iostream>
#include <vector>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "matrix4.h"
#include "shader.h"
#include "boid.h"

class Renderer {
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;

	Shader *shader;

	unsigned int VAO, VBO, EBO;

	Renderer();
	~Renderer();

	void init(float width, float height);
	void render(const std::vector<Boid>& boids);
	Matrix4 calculateProjectionMatrix(float width, float height);
	Matrix4 createModelMatrix(Vector2 position, float rotation);
};
