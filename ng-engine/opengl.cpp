#include "opengl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include "vector3.h"
#include "color.h"
#include "matrix4x4.h"

/*const char* vertexShaderSource = "attribute vec4 a_position;\n"
"uniform mat4 u_matrix;\n"
"void main()\n"
"{\n"
"   gl_Position = u_matrix * a_position;\n"
"}\0";*/

const char* vertexShaderSource = "attribute vec4 a_position;\n"
"void main()\n"
"{\n"
"    gl_Position.xyz = a_position.xyz;\n"
"    gl_Position.w = 1.0;\n"
"}\0";

//const char* fragmentShaderSource = "#version 330 core\n"
//"uniform vec4 u_color;\n"
//"out vec4 FragColor;"
//"\n"
//"void main()\n"
//"{\n"
//"	FragColor = u_color;"
//"}\n";

const char* fragmentShaderSource = "#version 430 core\n"
"out vec3 color;"
"\n"
"void main()\n"
"{\n"
"	color = vec3(1,0,0);\n"
"}\n";

void errorCallback(int error, const char* msg) {
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	std::cerr << s << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void debugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam) {
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	if (source == GL_DEBUG_SOURCE_API) {
		std::cout << "Source: API" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM) {
		std::cout << "Source: Window System" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER) {
		std::cout << "Source: Shader Compiler" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_THIRD_PARTY) {
		std::cout << "Source: Third Party" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_APPLICATION) {
		std::cout << "Source: Application" << std::endl;
	}
	else if (source == GL_DEBUG_SOURCE_OTHER) {
		std::cout << "Source: Other" << std::endl;
	} else {
		std::cout << "Source: Unknown" << std::endl;
	}

	if (type == GL_DEBUG_TYPE_ERROR) {
		std::cout << "Type: Error" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) {
		std::cout << "Type: Deprecated Behavior" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) {
		std::cout << "Type: Undefined Behavior" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_PORTABILITY) {
		std::cout << "Type: Portability" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_PERFORMANCE) {
		std::cout << "Type: Performance" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_MARKER) {
		std::cout << "Type: Marker" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_PUSH_GROUP) {
		std::cout << "Type: Push Group" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_POP_GROUP) {
		std::cout << "Type: Pop Group" << std::endl;
	}
	else if (type == GL_DEBUG_TYPE_OTHER) {
		std::cout << "Type: Other" << std::endl;
	}
	else {
		std::cout << "Type: Unknown" << std::endl;
	}

	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		std::cout << "Severity: High" << std::endl;
	}
	else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
		std::cout << "Severity: Medium" << std::endl;
	}
	else if (severity == GL_DEBUG_SEVERITY_LOW) {
		std::cout << "Severity: Low" << std::endl;
	}
	else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
		std::cout << "Severity: Notification" << std::endl;
	}
	else {
		std::cout << "Severity: Unknown" << std::endl;
	}
}

unsigned int createShader(GLenum type, const char* source) {
	unsigned int shader = glCreateShader(type);
	if (shader == 0) {
		throw std::exception("Failed to create shader.");
	}
	glShaderSource(shader, 1, &source, NULL);
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

unsigned int createProgram() {
	unsigned int program = glCreateProgram();

	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	glAttachShader(program, vertexShader);

	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
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

void OpenGL::draw(std::vector<Vector3> vertices, GLenum primitive) {
	std::vector<float> bytes;

	for (Vector3 vertex : vertices) {
		bytes.push_back(vertex.x());
		bytes.push_back(vertex.y());
		bytes.push_back(vertex.z());
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, bytes.size(), &bytes[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(this->positionLoc);
	glVertexAttribPointer(this->positionLoc, 3, GL_FLOAT, false, 0, 0);

	//if (primitive == GL_LINES || primitive == GL_LINE_STRIP || primitive == GL_LINE_LOOP) {
	//	float c[] = { 
	//		static_cast<float>(this->strokeColor.r()) / 255.0f, 
	//		static_cast<float>(this->strokeColor.g()) / 255.0f, 
	//		static_cast<float>(this->strokeColor.b()) / 255.0f, 
	//		1
	//	};
	//	glUniform4fv(this->colorLoc, 4, c);
	//} else {
	//	float c[] = { this->fillColor.r() / 255.0f, this->fillColor.g() / 255.0f, this->fillColor.b() / 255.0f, 1 };
	//	glUniform4fv(this->colorLoc, 4, c);
	//}

	glDrawArrays(primitive, 0, (GLsizei)vertices.size());

	glDisableVertexAttribArray(this->positionLoc);
}


OpenGL::OpenGL() {
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		throw std::exception();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); // this makes everything significantly slower !!!

	this->window = glfwCreateWindow(800, 600, "NG-ENGINE", nullptr, nullptr);
	if (this->window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		throw std::exception();
	}
	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw std::exception();
	}

	int flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(debugMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	GLuint vertexArrayObj;
	glGenVertexArrays(1, &vertexArrayObj);
	glBindVertexArray(vertexArrayObj);

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);

	unsigned int program = createProgram();
	glGenBuffers(1, &this->positionBuffer);

	this->positionLoc = glGetAttribLocation(program, "a_position");

	this->colorLoc = glGetUniformLocation(program, "u_color");
	this->matrixLoc = glGetUniformLocation(program, "u_matrix");

	glUseProgram(program);
	this->setTransformationMatrix(Matrix4x4::identity());
}

OpenGL::~OpenGL() {
	glfwTerminate();
}

void OpenGL::startOfFrame() {
	glClearColor(this->backgroundColor.r() / 255.0f, this->backgroundColor.g() / 255.0f, this->backgroundColor.b() / 255.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL::endOfFrame() {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void OpenGL::clear() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL::setTransformationMatrix(Matrix4x4 m) {
	float values[] = {
		m.a(), m.b(), m.c(), m.d(),
		m.e(), m.f(), m.g(), m.h(),
		m.i(), m.j(), m.k(), m.l(),
		m.m(), m.n(), m.o(), m.p(),
	};
	glUniformMatrix4fv(this->matrixLoc, 16, true, values);
}

void OpenGL::triangle() {
	Vector3 vertices[] = {
		Vector3(-0.5, -0.5, 0),
		Vector3(0.5, -0.5, 0),
		Vector3(0, 0.5, 0),
	};

	std::vector<Vector3> verticesAsVector = std::vector<Vector3>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
	this->draw(verticesAsVector, GL_TRIANGLES);
}

void OpenGL::rectangle() {
	Vector3 vertices[] = {
		Vector3(-0.5, -0.5, 0),
		Vector3(0.5, -0.5, 0),
		Vector3(-0.5, 0.5, 0),
		Vector3(0.5, 0.5, 0),
	};

	std::vector<Vector3> verticesAsVector = std::vector<Vector3>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
	this->draw(verticesAsVector, GL_TRIANGLE_STRIP);
}