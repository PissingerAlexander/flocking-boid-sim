#pragma once

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Program {
	public:
		Program();
		~Program();
		void destroy();

		void initWindow(const char *title, int width, int height);

		void run();

		void getFramebufferSize(int *width, int *height);
	private:
		GLFWwindow *window;

		bool windowSetup = false;
		bool running = false;

		void update();
		void render();

		static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
};
