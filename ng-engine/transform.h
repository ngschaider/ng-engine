#pragma once

#include "vector3.h"
#include "matrix4x4.h"
#include "component.h"
#include "quaternion.h"

class Transform : public Component {
public:
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;
	Transform* parent;
	Transform();
	Matrix4x4 getLocalToWorldMatrix();
};