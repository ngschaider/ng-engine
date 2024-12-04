#include "opengl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include "vector3.h"
#include <map>
#include "color.h"
#include "matrix4x4.h"
#include <string>
#include "shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

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
	} else if (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM) {
		std::cout << "Source: Window System" << std::endl;
	} else if (source == GL_DEBUG_SOURCE_SHADER_COMPILER) {
		std::cout << "Source: Shader Compiler" << std::endl;
	} else if (source == GL_DEBUG_SOURCE_THIRD_PARTY) {
		std::cout << "Source: Third Party" << std::endl;
	} else if (source == GL_DEBUG_SOURCE_APPLICATION) {
		std::cout << "Source: Application" << std::endl;
	} else if (source == GL_DEBUG_SOURCE_OTHER) {
		std::cout << "Source: Other" << std::endl;
	} else {
		std::cout << "Source: Unknown" << std::endl;
	}

	if (type == GL_DEBUG_TYPE_ERROR) {
		std::cout << "Type: Error" << std::endl;
	} else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) {
		std::cout << "Type: Deprecated Behavior" << std::endl;
	} else if (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR) {
		std::cout << "Type: Undefined Behavior" << std::endl;
	} else if (type == GL_DEBUG_TYPE_PORTABILITY) {
		std::cout << "Type: Portability" << std::endl;
	} else if (type == GL_DEBUG_TYPE_PERFORMANCE) {
		std::cout << "Type: Performance" << std::endl;
	} else if (type == GL_DEBUG_TYPE_MARKER) {
		std::cout << "Type: Marker" << std::endl;
	} else if (type == GL_DEBUG_TYPE_PUSH_GROUP) {
		std::cout << "Type: Push Group" << std::endl;
	} else if (type == GL_DEBUG_TYPE_POP_GROUP) {
		std::cout << "Type: Pop Group" << std::endl;
	} else if (type == GL_DEBUG_TYPE_OTHER) {
		std::cout << "Type: Other" << std::endl;
	} else {
		std::cout << "Type: Unknown" << std::endl;
	}

	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		std::cout << "Severity: High" << std::endl;
	} else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
		std::cout << "Severity: Medium" << std::endl;
	} else if (severity == GL_DEBUG_SEVERITY_LOW) {
		std::cout << "Severity: Low" << std::endl;
	} else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
		std::cout << "Severity: Notification" << std::endl;
	} else {
		std::cout << "Severity: Unknown" << std::endl;
	}

	return;
}


std::map<char, Character> loadCharacters() {
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		throw new std::exception("Could not init FreeType Library");
	}

	std::map<char, Character> characters;

	FT_Face face;
	if (FT_New_Face(ft, "C:/Windows/Fonts/arial.ttf", 0, &face)) {
		throw new std::exception("Failed to load font");
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			throw new std::exception("Failed to load glyph");
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			Vector2(face->glyph->bitmap.width * 1.0f, face->glyph->bitmap.rows * 1.0f),
			Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(int)face->glyph->advance.x
		};
		characters.insert(std::pair<char, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return characters;
}


void OpenGL::draw(std::vector<Vector3> vertices, GLenum primitive) {
	this->solidShader->use();

	std::vector<float> bytes;

	for (Vector3 vertex : vertices) {
		bytes.push_back(vertex.x());
		bytes.push_back(vertex.y());
		bytes.push_back(vertex.z());
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, bytes.size() * sizeof(float), &bytes[0], GL_STATIC_DRAW);

	int vertexAttribLoc = glGetAttribLocation(this->solidShader->id, "vertex");
	glEnableVertexAttribArray(vertexAttribLoc);
	glVertexAttribPointer(vertexAttribLoc, 3, GL_FLOAT, false, 0, 0);

	if (primitive == GL_LINES || primitive == GL_LINE_STRIP || primitive == GL_LINE_LOOP) {
		float c[] = {
			static_cast<float>(this->strokeColor.r()) / 255.0f,
			static_cast<float>(this->strokeColor.g()) / 255.0f,
			static_cast<float>(this->strokeColor.b()) / 255.0f,
			1
		};
		glUniform4fv(glGetUniformLocation(this->solidShader->id, "color"), 1, c);
	} else {
		float c[] = { this->fillColor.r() / 255.0f, this->fillColor.g() / 255.0f, this->fillColor.b() / 255.0f, 1 };
		glUniform4fv(glGetUniformLocation(this->solidShader->id, "color"), 1, c);
	}

	glDrawArrays(primitive, 0, (GLsizei)vertices.size());

	glDisableVertexAttribArray(vertexAttribLoc);
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

	this->textShader = new Shader("text.vs", "text.fs");
	this->solidShader = new Shader("solid.vs", "solid.fs");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	this->setTransformationMatrix(Matrix4x4::identity());

	this->textShader->use();
	this->characters = loadCharacters();
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

Vector2 OpenGL::size() {
	int width;
	int height;
	glfwGetWindowSize(this->window, &width, &height);
	return Vector2(width, height);
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
	glUniformMatrix4fv(glGetUniformLocation(this->solidShader->id, "projection"), 1, true, values);
	glUniformMatrix4fv(glGetUniformLocation(this->textShader->id, "projection"), 1, true, values);
}

void OpenGL::text(std::string text) {
	this->textShader->use();
}

void OpenGL::triangle() {
	Vector3 vertices[] = {
		Vector3(-0.5f, -0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(0.0f, 0.5f, 0.0f),
	};

	std::vector<Vector3> verticesAsVector = std::vector<Vector3>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
	this->draw(verticesAsVector, GL_TRIANGLES);
}

void OpenGL::rectangle() {
	Vector3 vertices[] = {
		Vector3(-0.5f, -0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(0.5f, 0.5f, 0.0f),
	};

	std::vector<Vector3> verticesAsVector = std::vector<Vector3>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
	this->draw(verticesAsVector, GL_TRIANGLE_STRIP);
}

Matrix4x4 OpenGL::getScreenToClipMatrix() {
	return this->getClipToScreenMatrix().invert();
}

Matrix4x4 OpenGL::getClipToScreenMatrix() {
	int width;
	int height;
	glfwGetWindowSize(this->window, &width, &height);
	return Matrix4x4::scale(Vector3(width, height, 1));
}