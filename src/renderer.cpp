#include "headers/constants.h"
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

void Renderer::render(GLFWwindow *window, std::vector<Boid>& boids) {
	// Create shader and load Projection matrix
	Shader shader = Shader("shaders/shader.vs", "shaders/shader.fs");
	shader.use();
	unsigned int projectionLocation = glGetUniformLocation(shader.Id, "projectionMatrix");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix.get());
	
	// Define Vertex and index data for boid
	float vertices[] = {
		0.0f, 1.0f, -1.0f,
		0.6f, -1.0f, -1.0f,
		0.0f, -0.5f, -1.0f,
		-0.6f, -1.0f, -1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	// Copy vertex and index data onto gpu
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	float now = 0;
	float previous = 0;
	running = true;
	while (running) {
		// Handle input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
		if (glfwWindowShouldClose(window)) {
			running = false;
			break;
		}

		// Clear screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (Boid& boid : boids) {
			// Create ModelMatrix for each boid
			Matrix4 modelMatrix = createModelMatrix(boid.position, boid.velocity);
			unsigned int modelLocation = glGetUniformLocation(shader.Id, "modelMatrix");
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, modelMatrix.get());

			// Draw Boid
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			boid.update(1, boids);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

Matrix4 Renderer::calculateProjectionMatrix(float width, float height) {
	return Matrix4(	2/width,	0,		0,				0,
			0,		2/height,	0,				0,
			0, 		0,		-(2/(100-0.1f)),		0,
			0, 		0,		-((100+0.1)/(100-0.1f)),	1);
}

Matrix4 Renderer::createModelMatrix(Vector2 position, Vector2 velocity) {
	float rotation = std::atan2(velocity.x, velocity.y);
	Matrix4 rotationMatrix = Matrix4(	cos(rotation), -sin(rotation), 0, 0,
						sin(rotation), cos(rotation), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);
	Matrix4 translationMatrix = Matrix4(	8, 0, 0, 0,
						0, 8, 0, 0,
						0, 0, 1, 0,
						position.x, position.y, -1, 1);
	return translationMatrix * rotationMatrix;
}
