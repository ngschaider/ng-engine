#include "shader.h"
#include <string>
#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "matrix4x4.h"
#include "vector3.h"

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
		std::cout << "Error during shader compilation: " << std::endl;
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

Shader::~Shader() {
	glDeleteProgram(this->id);
}

void Shader::use() {
	glUseProgram(this->id);
}

void Shader::setMatrix4x4(const std::string& name, Matrix4x4 m) const {
	float values[] = {
		m.a(), m.b(), m.c(), m.d(),
		m.e(), m.f(), m.g(), m.h(),
		m.i(), m.j(), m.k(), m.l(),
		m.m(), m.n(), m.o(), m.p(),
	};
	//float values[] = {
	//	m.a(), m.e(), m.i(), m.m(),
	//	m.b(), m.f(), m.j(), m.n(),
	//	m.c(), m.g(), m.k(), m.o(),
	//	m.d(), m.h(), m.l(), m.p(),
	//};
	glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, false, values);
}

void Shader::setVector3(const std::string& name, Vector3 v) const {
	float values[] = { v.x(), v.y(), v.z() };
	glUniform3fv(glGetUniformLocation(this->id, name.c_str()), 1, values);
}