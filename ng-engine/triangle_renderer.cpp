#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "triangle_renderer.h"
#include "resource_manager.h"
#include "color.h"

TriangleRenderer::TriangleRenderer() {
	this->shader = ResourceManager::loadShader("solid_vertex.glsl", "solid_fragment.glsl");

	// set up common VBO
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // bottom left
		0.5f, -0.5f, 0.0f, // bottom right
		0.0f, 0.433f, 0.0f, // top
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// setting up fill
	glGenVertexArrays(1, &this->VAO_fill);
	glBindVertexArray(this->VAO_fill);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // TODO: do we need this bind here? does the VAO capture the binding if the VBO is bound before the VAO?

	float indices_fill[] = { 0, 1, 2 };
	unsigned int EBO_fill;
	glGenBuffers(1, &EBO_fill);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_fill);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_fill), indices_fill, GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// setting up stroke
	glGenVertexArrays(1, &this->VAO_stroke);
	glBindVertexArray(this->VAO_stroke);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
}

void TriangleRenderer::render() {
	this->shader->use();
	this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix());

	if (this->doFill) {
		Vector4 c = Vector4((float)this->fillColor.r(), (float)this->fillColor.g(), (float)this->fillColor.b(), 255);
		this->shader->setVector4("color", c / 255);

		glBindVertexArray(this->VAO_fill);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	if (this->doStroke) {
		Vector4 c = Vector4((float)this->strokeColor.r(), (float)this->strokeColor.g(), (float)this->strokeColor.b(), 255);
		this->shader->setVector4("color", c / 255);

		glBindVertexArray(this->VAO_stroke);
		glDrawArrays(GL_LINES, 0, 8);
		glBindVertexArray(0);
	}
}