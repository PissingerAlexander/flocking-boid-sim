#include <iostream>

#include "headers/constants.h"
#include "headers/program.h"
#include "headers/shader.h"

int main() {
	Program program = Program();
	program.initWindow("Test", WIDTH, HEIGHT);
	program.run();

	return 0;
}

