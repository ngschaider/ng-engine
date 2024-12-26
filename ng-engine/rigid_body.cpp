#include "rigid_body.h"
#include "transform.h"

RigidBody::RigidBody() {

}

void RigidBody::fixedUpdate() {
	this->linearVelocity = this->linearVelocity + this->linearAcceleration;
	this->transform()->position = this->transform()->position + this->linearVelocity;

	this->angularVelocity = this->angularVelocity * this->angularAcceleration;
	this->transform()->rotation = this->transform()->rotation * this->angularVelocity;
}