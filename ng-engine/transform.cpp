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
	return this->localToWorld(this->position);
}