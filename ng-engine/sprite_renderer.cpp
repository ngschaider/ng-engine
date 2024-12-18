#include "sprite_renderer.h"
#include "texture2d.h"
#include "resource_manager.h"

SpriteRenderer::SpriteRenderer() {
	this->shader = ResourceManager::loadShader("sprite.vs", "sprite.fs");

	this->texture = nullptr;

	unsigned int VBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &this->VAO);
}


void SpriteRenderer::render() {
	this->shader->use();

	if (this->texture == nullptr) return;

	Matrix4x4 transformationMatrix = this->getTransformationMatrix();
	this->shader->setMatrix4x4("transformation", transformationMatrix);

	// this->shader->setVector3("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	this->texture->bind();

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}