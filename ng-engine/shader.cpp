#include "shader.h"
#include <string>
#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int createShader(GLenum type, std::string source) {
	unsigned int shader = glCreateShader(type);
	if (shader == 0) {
		throw std::exception("Failed to create shader.");
	}
	const char* constSource = source.c_str();
	glShaderSource(shader, 1, &constSource, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		char msg[512];
		glGetShaderInfoLog(shader, 512, NULL, msg);
		std::cout << msg << std::endl;
		glDeleteShader(shader);
		throw std::exception("Failed to compile shader");
	}

	return shader;
}

unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader) {
	unsigned int program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		char msg[512];
		glGetProgramInfoLog(program, 512, NULL, msg);
		std::cout << msg << std::endl;
		glDeleteProgram(program);
		throw std::exception("Failed to link program");
	}

	//glDetachShader(program, vertexShader);
	//glDetachShader(program, fragmentShader);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	return program;
}

std::string read(const char* path) {
	std::stringstream stream;
	std::ifstream file;
	file.open(path);
	stream << file.rdbuf();
	file.close();
	return stream.str();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, read(vertexPath));
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, read(fragmentPath));
	this->id = createProgram(vertexShader, fragmentShader);
}

void Shader::use() {
	glUseProgram(this->id);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}