#pragma once
#include "collider_2d.h"
#include "rect.h"
#include <exception>
#include "matrix4x4.h"
#include "transform.h"
#include "vector4.h"
#include "imgui.h"
#include "resource_manager.h"

Collider2D::Collider2D() {
	this->shader = ResourceManager::loadShader("solid_vertex.glsl", "solid_fragment.glsl");
	this->space = RendererSpace::Local;


	// setting up stroke
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glLineWidth(2);

	float vertices[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
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

Rect Collider2D::getLocalBounds() {
	throw new std::exception("Collider2D::getLocalBounds has to be overwritten in child classes.");
}

Rect Collider2D::getGlobalBounds() {
	Rect local = this->getLocalBounds();
	Matrix4x4 m = this->transform()->getLocalToWorldMatrix();

	Vector2 min = (m * local.bottomLeft().toVector4(0, 0)).xy();
	Vector2 max = (m * local.topRight().toVector4(0, 0)).xy();

	return Rect(min, max - min, AnchorPoint::BottomLeft);
}

void Collider2D::render() {
	if (!this->drawAABB) {
		return;
	}

	Rect bounds = this->getLocalBounds();
	//Rect bounds = Rect(Vector2(0.1, 0), Vector2(1, 1), AnchorPoint::BottomLeft);
	Matrix4x4 m = Matrix4x4::TRS(bounds.bottomLeft().toVector3(0), Quaternion::identity(), bounds.size().toVector3(1));
	this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix() * m);
	this->shader->setVector4("color", Vector4(0, 0, 1, 1));

	glBindVertexArray(this->VAO);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}