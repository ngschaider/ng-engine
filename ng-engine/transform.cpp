#include "transform.h"
#include "matrix4x4.h"

Transform::Transform() {
	this->position = Vector3(0, 0, 0);
	this->scale = Vector3(1, 1, 1);
	this->rotation = Quaternion::identity();
	this->parent = nullptr;
}

Matrix4x4 Transform::getLocalToWorldMatrix() {
	Matrix4x4 myMatrix = Matrix4x4::TRS(this->position, this->rotation, this->scale);

	if (this->parent == nullptr) {
		return myMatrix;
	}

	return this->parent->getLocalToWorldMatrix() * myMatrix;
}