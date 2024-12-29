#include <cassert>
#include <exception>
#include <vector>
#include "collider_2d.h"
#include "glad/glad.h"
#include "matrix4x4.h"
#include "quaternion.h"
#include "rect.h"
#include "renderer.h"
#include "resource_manager.h"
#include "transform.h"
#include "vector2.h"
#include "vector4.h"

Collider2D::Collider2D() {
	this->shader = ResourceManager::loadShader("solid_vertex.glsl", "solid_fragment.glsl");
	this->space = RendererSpace::World;

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

	this->onCollisionStart.on([this](Collider2D* other) {
		this->collidingWith.push_back(other);
	});

	this->onCollisionEnd.on([this](Collider2D* other) {
		std::vector<Collider2D*>::iterator it = std::find(this->collidingWith.begin(), this->collidingWith.end(), other);
		assert(it != this->collidingWith.end());

		this->collidingWith.erase(it);
	});
}

Rect Collider2D::getLocalBounds() {
	throw new std::exception("Collider2D::getLocalBounds has to be overwritten in child classes.");
}

Rect Collider2D::getWorldBounds() {
	Rect local = this->getLocalBounds();
	Transform* transform = this->transform();
	Matrix4x4 m = transform->getLocalToWorldMatrix();

	Vector2 min = (m * local.bottomLeft().toVector4(1, 1)).xy();
	Vector2 max = (m * local.topRight().toVector4(1, 1)).xy();

	return Rect(min, max - min, AnchorPoint::BottomLeft);
}

void Collider2D::render() {
	if (!this->drawAABB) {
		return;
	}

	this->shader->use();

	// Rect bounds = this->getLocalBounds();
	// Matrix4x4 m = Matrix4x4::TRS(bounds.bottomLeft().toVector3(0), Quaternion::identity(), bounds.size().toVector3(1));
	// this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix() * m);

	Rect bounds = this->getWorldBounds();
	Matrix4x4 m = Matrix4x4::TRS(bounds.bottomLeft().toVector3(0), Quaternion::identity(), bounds.size().toVector3(1));
	this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix() * m);

	if(this->collidingWith.size() > 0) {
		this->shader->setVector4("color", Vector4(1, 0, 0, 1));
	}
	else {
		this->shader->setVector4("color", Vector4(0, 0, 1, 1));
	}
	

	glBindVertexArray(this->VAO);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}