#pragma once

#include <iostream>
#include <vector>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "matrix4.h"
#include "shader.h"
#include "boid.h"

class Renderer {
	public:
		Renderer();
		~Renderer();

		void init(float width, float height);
		void render(GLFWwindow *window, const std::vector<Boid>& boids);

	private:
		bool running = false;

		Matrix4 viewMatrix;
		Matrix4 projectionMatrix;

		unsigned int VAO, VBO, EBO;

		Matrix4 calculateProjectionMatrix(float width, float height);
		Matrix4 createModelMatrix(Vector2 position, float rotation);
};
