#include "transform.h"
#include "matrix4x4.h"
#include "quaternion.h"
#include "vector3.h"
#include "scene.h"

Matrix4x4 Transform::getLocalToWorldMatrix() {
	return Matrix4x4::TRS(this->getGlobalPosition(), this->getGlobalRotation(), this->getGlobalScale());
}

Vector4 Transform::localToWorld(Vector4 local) {
	return this->getLocalToWorldMatrix() * local;
}

Vector3 Transform::localToWorld(Vector3 local) {
	return this->localToWorld(local.toVector4(1)).xyz();
}

Vector2 Transform::localToWorld(Vector2 local) {
	return this->localToWorld(Vector3(local.x(), local.y(), 1)).xy();
}

float Transform::localToWorld(float local) {
	return local * this->getLocalToWorldMatrix().a();
}


Matrix4x4 Transform::getWorldToLocalMatrix() {
	return this->getLocalToWorldMatrix().invert();
}

Vector4 Transform::worldToLocal(Vector4 world) {
	return this->getWorldToLocalMatrix() * world;
}

Vector3 Transform::worldToLocal(Vector3 world) {
	return this->worldToLocal(world.toVector4(1)).xyz();
}

Vector2 Transform::worldToLocal(Vector2 world) {
	return this->worldToLocal(Vector3(world.x(), world.y(), 1)).xy();
}

float Transform::worldToLocal(float world) {
	return this->getWorldToLocalMatrix().a() * world;
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

Vector3 Transform::getGlobalPosition() {
	if (this->transform()->parent == nullptr) {
		return this->position;
	}

	return this->transform()->parent->getGlobalPosition() + this->position;
}

Quaternion Transform::getGlobalRotation() {
	if (this->transform()->parent == nullptr) {
		return this->rotation;
	}

	return this->transform()->parent->getGlobalRotation() * this->rotation;
}

Vector3 Transform::getGlobalScale() {
	if (this->transform()->parent == nullptr) {
		return this->scale;
	}

	Vector3 parentScale = this->transform()->parent->getGlobalScale();
	return Vector3(parentScale.x() * this->scale.x(), parentScale.y() * this->scale.y(), parentScale.z() * this->scale.z());
}