#include "opengl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include "vector3.h"
#include "matrix4x4.h"

const char* vertexShaderSource = "attribute vec4 a_position;\n"
"uniform mat4 u_matrix;\n"
"void main()\n"
"{\n"
"   gl_Position = u_matrix * a_position\n"
"}\0";

const char* fragmentShaderSource = "precision mediump float;\n"
"uniform vec4 u_color;\n"
"\n"
"void main()\n"
"{\n"
"	gl_FragColor = u_color"
"}\n";

void errorCallback(int error, const char* msg) {
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	std::cerr << s << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

unsigned int createShader(unsigned int type, const char* source) {
	unsigned int shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char msg[512];
		glGetShaderInfoLog(shader, 512, NULL, msg);
		std::cout << msg << std::endl;
		glDeleteShader(shader);
		throw std::exception("Failed to compile shader");
	}

	return shader;
}

unsigned int createProgram() {
	unsigned int program = glCreateProgram();

	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	glAttachShader(program, vertexShader);

	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char msg[512];
		glGetProgramInfoLog(program, 512, NULL, msg);
		std::cout << msg << std::endl;
		glDeleteProgram(program);
		throw std::exception("Failed to link program");
	}
}

void OpenGL::draw(std::vector<Vector3> vertices, unsigned int primitive) {
	std::vector<float> bytes;

	for (Vector3 vertex : vertices) {
		bytes.push_back(vertex.x());
		bytes.push_back(vertex.y());
		bytes.push_back(vertex.z());
	}

	glEnableVertexAttribArray(this->positionLoc);
	glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, bytes.size(), &bytes[0], GL_STATIC_DRAW);
	glVertexAttribPointer(this->positionLoc, 3, GL_FLOAT, false, 0, 0);

	if (primitive == GL_LINES || primitive == GL_LINE_STRIP || primitive == GL_LINE_LOOP) {
		float c[] = { this->strokeColor.r(), this->strokeColor.g(), this->strokeColor.b(), 1};
		glUniform4fv(this->colorLoc, 4, c);
	}
	else {
		float c[] = { this->fillColor.r(), this->fillColor.g(), this->fillColor.b(), 1 };
		glUniform4fv(this->colorLoc, 4, c);
	}

	glDrawArrays(primitive, 0, vertices.size());
}


OpenGL::OpenGL() {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		throw std::exception();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "NG-ENGINE", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		throw std::exception();
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw std::exception();
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);



	while (!glfwWindowShouldClose(window)) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, true);
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

OpenGL::~OpenGL() {
	glfwTerminate();
}

OpenGL::clear() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

OpenGL::setTransformationMatrix(Matrix4x4 m) {
	glUniformMatrix4fv(this->matrixLoc, false, )
}