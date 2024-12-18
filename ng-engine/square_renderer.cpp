
#include "square_renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resource_manager.h"
#include "vector4.h"

SquareRenderer::SquareRenderer() {
	this->shader = ResourceManager::loadShader("solid_vertex.glsl", "solid_fragment.glsl");
	
	// setting up common
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

	// setting up fill
	glGenVertexArrays(1, &this->VAO_fill);
	glBindVertexArray(this->VAO_fill);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // TODO: do we need this bind here? does the VAO capture the binding if the VBO is bound before the VAO?

	unsigned int indices_fill[] = { 0, 1, 3, 2 };
	unsigned int EBO_fill;
	glGenBuffers(1, &EBO_fill);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_fill);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_fill), indices_fill, GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);

	// setting up stroke
	glGenVertexArrays(1, &this->VAO_stroke);
	glBindVertexArray(this->VAO_stroke);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // TODO: do we need this bind here? does the VAO capture the binding if the VBO is bound before the VAO?

	unsigned int indices_stroke[] = { 0, 1, 2, 3 };
	unsigned int EBO_stroke;
	glGenBuffers(1, &EBO_stroke);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_stroke);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_fill), indices_stroke, GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
}

SquareRenderer::~SquareRenderer() {
	glDeleteVertexArrays(1, &this->VAO_fill);
	glDeleteVertexArrays(1, &this->VAO_stroke);
}

void SquareRenderer::render() {
	this->shader->use();
	this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix());

	if (this->doFill) {
		Vector4 c = Vector4((float) this->fillColor.r(), (float) this->fillColor.g(), (float) this->fillColor.b(), 255);
		this->shader->setVector4("color", c / 255);

		glBindVertexArray(this->VAO_fill);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	if (this->doStroke) {
		Vector4 c = Vector4((float) this->strokeColor.r(), (float) this->strokeColor.g(), (float) this->strokeColor.b(), 255);
		this->shader->setVector4("color", c / 255);
		
		glBindVertexArray(this->VAO_stroke);
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}