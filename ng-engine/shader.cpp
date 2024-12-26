#include "shader.h"
#include <string>
#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "matrix4x4.h"
#include "vector2.h"
#include "vector2i.h"
#include "vector3.h"
#include "vector4.h"

std::string read(const char* path) {
	std::stringstream stream;
	std::ifstream file;
	file.open(path);

	if (!file.good()) {
		throw new std::exception("Could not open shader source file");
	}

	stream << file.rdbuf();
	file.close();

	return stream.str();
}

unsigned int createShader(const GLenum type, const std::string sourceFile) {
	unsigned int shader = glCreateShader(type);
	if (shader == 0) {
		throw std::exception("Failed to create shader.");
	}

	const char* sourceFileStr = sourceFile.c_str();
	const std::string source = read(sourceFileStr);
	const char* sourceStr = source.c_str();

	glShaderSource(shader, 1, &sourceStr, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		char msg[512];
		glGetShaderInfoLog(shader, 512, NULL, msg);
		std::cout << "Error during shader compilation: " << std::endl;
		std::cout << msg << std::endl;
		glDeleteShader(shader);
		throw std::exception("Failed to compile shader.");
	}

	return shader;
}

unsigned int createProgram(const char* vertexFile, const char* fragmentFile) {
	unsigned int program = glCreateProgram();

	glAttachShader(program, createShader(GL_VERTEX_SHADER, vertexFile));
	glAttachShader(program, createShader(GL_FRAGMENT_SHADER, fragmentFile));

	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		char msg[512];
		glGetProgramInfoLog(program, 512, NULL, msg);
		std::cout << msg << std::endl;
		glDeleteProgram(program);
		throw std::exception("Failed to link program.");
	}

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	return program;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	this->id = createProgram(vertexFile, fragmentFile);
}

Shader::~Shader() {
	glDeleteProgram(this->id);
}

void Shader::use() {
	glUseProgram(this->id);
}

void Shader::setFloat(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setInteger(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setVector2(const char* name, Vector2 value) const {
	glUniform2f(glGetUniformLocation(this->id, name), value.x(), value.y());
}

void Shader::setVector2i(const char* name, Vector2i value) const {
	glUniform2i(glGetUniformLocation(this->id, name), value.x(), value.y());
}

void Shader::setVector3(const char* name, Vector3 value) const {
	glUniform3f(glGetUniformLocation(this->id, name), value.x(), value.y(), value.z());
}

void Shader::setVector4(const char* name, Vector4 value) const {
	glUniform4f(glGetUniformLocation(this->id, name), value.x(), value.y(), value.z(), value.w());
}

void Shader::setMatrix3x3(const char* name, Matrix3x3 m) const {
	float values[] = {
		m.a(), m.d(), m.g(),
		m.b(), m.e(), m.h(),
		m.c(), m.f(), m.i(),
	};
	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, false, values);
}

void Shader::setMatrix4x4(const char* name, Matrix4x4 m) const {
	float values[] = {
		m.a(), m.e(), m.i(), m.m(),
		m.b(), m.f(), m.j(), m.n(),
		m.c(), m.g(), m.k(), m.o(),
		m.d(), m.h(), m.l(), m.p(),
	};
	auto location = glGetUniformLocation(this->id, name);
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, values);
}