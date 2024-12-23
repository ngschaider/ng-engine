#pragma once

#include "component.h"
#include "vector3.h"
#include "quaternion.h"

class RigidBody : public Component {
public:
	float mass = 1.0f;
	float restitution = 0.8f;
	RigidBody();
	Vector3 linearAcceleration = Vector3(0, 0, 0);
	Quaternion angularAcceleration = Quaternion::identity();
	Vector3 linearVelocity = Vector3(0, 0, 0);
	Quaternion angularVelocity = Quaternion::identity();
	void update();
};