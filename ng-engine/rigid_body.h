#pragma once

#include "component.h"
#include "quaternion.h"
#include "vector3.h"

/**
* Adds physical properties to game objects. This is primarily used for the collision system to resolve collisions realistically.
* If you do not want the game object to be moved by collisions, set the mass of the rigid body to INFINITY.
*/
class RigidBody : public Component {
public:
	/**
	* The mass of the rigid body.
	*/
	float mass = 1.0f;

	/**
	* The restitution specifies the "bounciness" of the object. Lower values mean that more energy is losed during collisions. Higher values mean more energy is conserved.
	* This value should always be between zero and one. Set this to one for 100% elastic bounces (no energy loss).
	*/
	float restitution = 1.0f;

	/**
	* The linear acceleration of the rigid body.
	* The linear velocity gets increased by this acceleration every fixedUpdate.
	*/
	Vector3 linearAcceleration = Vector3(0, 0, 0);

	/**
	* The angular acceleration of the rigid body.
	* The angular velocity gets increased by this acceleration every fixedUpdate.
	*/
	Quaternion angularAcceleration = Quaternion::identity();

	/**
	* The linear velocity of the rigid body.
	* The position gets increased by this velocity every fixedUpdate.
	*/
	Vector3 linearVelocity = Vector3(0, 0, 0);

	/**
	* The angular velocity of the rigid body.
	* The rotation gets increased by this velocity every fixedUpdate.
	*/
	Quaternion angularVelocity = Quaternion::identity();

	void fixedUpdate() override;
};