#include <iostream>
#include <random>

#include "headers/program.h"
#include "headers/shader.h"

int main() {
	srand(time(nullptr));

	Program program = Program();
	program.initWindow("Test", 1280, 720);
	
	Shader shader = Shader("shaders/shader.vs", "shaders/shader.fs");

	program.run();


	return 0;
}

