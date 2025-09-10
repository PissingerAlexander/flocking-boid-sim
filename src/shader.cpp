#include "headers/shader.h"

Shader::Shader() {};

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;

	vertexShaderFile.exceptions(std::istream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::istream::failbit | std::ifstream::badbit);
	try {
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);
		std::stringstream vertexShaderStream, fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	} catch (std::ifstream::failure error) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char * vertexShaderCode = vertexCode.c_str();
	const char * fragmentShaderCode = fragmentCode.c_str();
	
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	Id = glCreateProgram();
	glAttachShader(Id, vertex);
	glAttachShader(Id, fragment);
	glLinkProgram(Id);

	glGetProgramiv(Id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(Id, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(Id);
}
