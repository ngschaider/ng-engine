#include "line_renderer.h"
#include "glad/glad.h"
#include "resource_manager.h"

LineRenderer::LineRenderer() {
	this->shader = ResourceManager::loadShader("solid_vertex.glsl", "solid_fragment.glsl");
	this->space = RendererSpace::World;

	
	// setting up stroke
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glLineWidth(2);

	float vertices[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int indices[] = { 0, 1, 2, 3 };
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	glBindVertexArray(0);
}

void LineRenderer::render() {
	Vector3 diff = this->start - this->end;
	Matrix4x4 m = Matrix4x4::rotate(Quaternion(diff.x(), diff.y(), diff.z(), 1)) * Matrix4x4::translate(this->start);
	this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix() * m);
	this->shader->setVector4("color", Vector4(0, 0, 1, 1));

	glBindVertexArray(this->VAO);
	glLineWidth(2);
	glDrawElements(GL_LINE, 2, GL_FLOAT, 0);
	glBindVertexArray(0);
}