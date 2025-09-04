#include <iostream>
#include <math.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "header/matrix/matrices.h"
#include "header/vector/vectors.h"
#include "header/shader/shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "header/image/stb_image.h"

void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void calculateOrthFrustum(Matrix4 *projectionMatrix, int width, int height, float near, float far);

float vertices[] = {
	 80.0f,  80.0f, 0.0f,	1.0f, 0.0f, // TOP   RIGHT
	 80.0f, -80.0f, 0.0f,	1.0f, 1.0f, // LOWER RIGHT
	-80.0f, -80.0f, 0.0f,	0.0f, 1.0f, // LOWER LEFT
	-80.0f,  80.0f, 0.0f,	0.0f, 0.0f, // TOP   LEFT
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {
	unsigned int width = 1280;
	unsigned int height = 720;

	// GLFW init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Winodw creation
	GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	// Load GL function pointers
	if (!gladLoadGL(glfwGetProcAddress)) {
		std::cout << "Failed to load initialize GLAD" << std::endl;
		return 1;
	}

	Shader ourShader("./shader/shader.vs", "./shader/shader.fs");
	
	Matrix4 modelMatrix = Matrix4(	1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
	
	Matrix4 viewMatrix = Matrix4(	1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, -2, 1);
	Matrix4 projectionMatrix;
	calculateOrthFrustum(&projectionMatrix, width, height, 0.1f, 100.0f);

	// Set up vertex buffers and configure vertex attributes
	// ### USING VAO ###
	unsigned int VAO, VBO, EBO;
	// Gen vertex array object, vertex buffer object and element buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO and copy vertex position data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind EBO and copy index data into EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set vertex attributes pointer for position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// Set vertex attributes pointer for textures
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Do NOT unbind EBO while VBO is bound
	// !glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	// You can unbind the VAO afterwards
	glBindVertexArray(0);

	unsigned int texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int imgWidth, imgHeight, nrChannels;
	unsigned char *data = stbi_load("textures/container.jpg", &imgWidth, &imgHeight, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "ERROR: Failed to load texture nr 1" << std::endl;
	}
	stbi_image_free(data);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE

	// Use shader program
	ourShader.use();
	ourShader.setInt("texture", 0);

	while (!glfwWindowShouldClose(window)) {
		// Input
		processInput(window);

		// Clear screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		ourShader.use();

		int modelLocation = glGetUniformLocation(ourShader.ID, "model");
		int viewLocation = glGetUniformLocation(ourShader.ID, "view");
		int projectionLocation = glGetUniformLocation(ourShader.ID, "projection");

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, modelMatrix.get());
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.get());
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix.get());

		// Draw elements
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glBindVertexArray(0); // no need to unbind it every time

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void calculateOrthFrustum(Matrix4 *projectionMatrix, int width, int height, float near, float far) {
	float mat0 = 2.0f / (float)width;
	float mat5 = 2.0f / (float)height;
	float mat10 = -2.0f / (far - near);
	float mat11 = -((far + near)/(far - near));

	float row0[4] = {mat0, 0, 0, 0};
	float row1[4] = {0, mat5, 0, 0};
	float row2[4] = {0, 0, mat10, mat11};
	float row3[4] = {0, 0, 0, 1};

	projectionMatrix->setRow(0, row0);
	projectionMatrix->setRow(1, row1);
	projectionMatrix->setRow(2, row2);
	projectionMatrix->setRow(3, row3);
}
