#include "transform.h"
#include "matrix4x4.h"
#include "quaternion.h"
#include "vector3.h"

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