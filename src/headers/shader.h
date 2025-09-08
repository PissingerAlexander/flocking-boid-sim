#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include <glad/gl.h>

class Shader {
	public:
		unsigned int Id;
		Shader(const char *vertexPath, const char *fragmentPath);

		void use();
};
