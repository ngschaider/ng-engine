#include "render_system.h"
#include "opengl.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

RenderSystem::RenderSystem() {
	this->graphics = new OpenGL();
}

RenderSystem::~RenderSystem() {
	if (this->graphics != nullptr) {
		delete this->graphics;
	}
}

void RenderSystem::update() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}