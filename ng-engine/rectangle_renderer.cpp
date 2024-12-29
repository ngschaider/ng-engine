
#include "rectangle_renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resource_manager.h"
#include "vector4.h"

RectangleRenderer::RectangleRenderer() {
	this->shader = ResourceManager::loadShader("solid_vertex.glsl", "solid_fragment.glsl");

	// setting up fill
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // bottom left
		0.5f, -0.5f, 0.0f, // bottom right
		0.5f, 0.5f, 0.0f, // top right
		-0.5f, 0.5f, 0.0f, // top left
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int indices[] = { 0, 1, 3, 2 };
	unsigned int EBO_fill;
	glGenBuffers(1, &EBO_fill);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_fill);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
}

RectangleRenderer::~RectangleRenderer() {
	glDeleteVertexArrays(1, &this->VAO);
}

void RectangleRenderer::render() {
	this->shader->use();
	this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix());

	if (this->doFill) {
		Vector4 c = Vector4((float) this->fillColor.r(), (float) this->fillColor.g(), (float) this->fillColor.b(), 255);
		this->shader->setVector4("color", c / 255);

		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}