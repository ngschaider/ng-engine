#pragma once

#include "component.h"
#include "vector3.h"
#include "quaternion.h"

class RigidBody : public Component {
public:
	Vector3 linearAcceleration;
	Quaternion angularAcceleration;
	Vector3 linearVelocity;
	Quaternion angularVelocity;
	float mass;
	void update();


};