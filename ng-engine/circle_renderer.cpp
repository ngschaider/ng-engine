#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "circle_renderer.h"
#include "resource_manager.h"
#include "color.h"

CircleRenderer::CircleRenderer() {
	this->shader = ResourceManager::loadShader("circle_vertex.glsl", "circle_fragment.glsl");

	// setting up fill
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	float vertices[] = {
		0.5f, -0.5f, 0, 1.0f, -1.0f,
		0.5f, 0.5f, 0, 1.0f, 1.0f,
		-0.5f, 0.5f, 0, -1.0f, 1.0f,
		-0.5f, -0.5f, 0, -1.0f, -1.0f,
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//float indices_fill[] = { 0, 1, 2, 3 };
	//unsigned int EBO_fill;
	//glGenBuffers(1, &EBO_fill);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_fill);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_fill), indices_fill, GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(glGetAttribLocation(this->shader->id, "vertex"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "value"));
	glVertexAttribPointer(glGetAttribLocation(this->shader->id, "value"), 2, GL_FLOAT, GL_FALSE, 20, (void*) (3 * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CircleRenderer::render() {
	this->shader->use();

	this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix());

	Vector4 c = Vector4((float)this->fillColor.r(), (float)this->fillColor.g(), (float)this->fillColor.b(), 255);
	this->shader->setVector4("color", c / 255);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}