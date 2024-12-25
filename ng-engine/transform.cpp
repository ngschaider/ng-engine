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

Matrix4x4 Transform::getWorldToLocalMatrix() {
	return this->getLocalToWorldMatrix().invert();
}

Vector3 Transform::localToWorld(Vector3 local) {
	return (this->getLocalToWorldMatrix() * local.toVector4(1)).xyz();
}

Vector2 Transform::localToWorld(Vector2 local) {
	return this->localToWorld(Vector3(local.x(), local.y(), 1)).xy();
}

float Transform::localToWorld(float local) {
	return this->localToWorld(Vector2(local, 1)).x();
}

Vector3 Transform::worldToLocal(Vector3 world) {
	return (this->getWorldToLocalMatrix() * world.toVector4(1)).xyz();
}

Vector2 Transform::worldToLocal(Vector2 world) {
	return this->worldToLocal(Vector3(world.x(), world.y(), 1)).xy();
}

float Transform::worldToLocal(float world) {
	return this->worldToLocal(Vector3(world, 1, 1)).x();
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