#include "transform.h"
#include "matrix4x4.h"
#include "quaternion.h"
#include "vector3.h"
#include "scene.h"

Transform::Transform() {
	this->position = Vector3(0, 0, 0);
	this->rotation = Quaternion::identity();
	this->scale = Vector3(1, 1, 1);
	this->parent = nullptr;
}

Matrix4x4 Transform::getLocalToWorldMatrix() {
	Matrix4x4 myMatrix = Matrix4x4::TRS(this->position, this->rotation, this->scale);

	if (this->parent == nullptr) {
		return myMatrix;
	}

	return this->parent->getLocalToWorldMatrix() * myMatrix;
}

void Transform::move(Vector3 vector) {
	this->position = this->position + vector;
}

void Transform::move(Vector2 vector) {
	this->move(vector.toVector3(0));
}

std::vector<Transform*> Transform::getChildren() {
	std::vector<Transform*> children;

	std::vector<Transform*> allTransforms = this->scene()->getComponents<Transform>();
	for (Transform* transform : allTransforms) {
		if (transform->parent == this) {
			children.push_back(transform);
		}
	}

	return children;
}