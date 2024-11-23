#include "rigid_body.h"
#include "transform.h"

void RigidBody::update() {
	this->linearVelocity = this->linearVelocity + this->linearAcceleration;
	this->transform()->position = this->transform()->position + this->linearVelocity;

	this->angularVelocity = this->angularVelocity + this->angularAcceleration;
	this->transform()->rotation = this->transform()->rotation + this->angularVelocity;
}