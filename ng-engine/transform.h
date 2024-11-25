#pragma once

#include "vector3.h"
#include "matrix4x4.h"
#include "component.h"
#include "quaternion.h"

class Transform : public Component {
public:
	Vector3 position = Vector3(0, 0, 0);
	Quaternion rotation = Quaternion::identity();
	Vector3 scale = Vector3(1, 1, 1);
	Transform* parent = nullptr;
	Transform();
	Matrix4x4 getLocalToWorldMatrix();
};