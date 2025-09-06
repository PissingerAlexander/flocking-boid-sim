#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <GLFW/glfw3.h>
#include <glad/gl.h>

class Program {
	public:
		Program();
		~Program();
		void destroy();

		void initWindow(const char *title, int width, int height);

		void run();

		void getFramebufferSize(int *width, int *height);
	private:
		GLFWWindow *window;

		bool windowSetup = false;
		bool running = false;

		void update();
		void render();

		static void FramebufferSizeCallback(GLFWWindow *window, int width, int height);
};
