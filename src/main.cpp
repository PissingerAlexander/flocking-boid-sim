#include <iostream>
#include <math.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "header/shader/shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "header/image/stb_image.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

float vertices[] = {
	 0.5f,  0.5f, 0.0f,	1.0f, 0.0f, // TOP   RIGHT
	 0.5f, -0.5f, 0.0f,	1.0f, 1.0f, // LOWER RIGHT
	-0.5f, -0.5f, 0.0f,	0.0f, 1.0f, // LOWER LEFT
	-0.5f,  0.5f, 0.0f,	0.0f, 0.0f, // TOP   LEFT
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {
	// GLFW init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Winodw creation
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

	int width, height, nrChannels;
	unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection;

		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f),  (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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
