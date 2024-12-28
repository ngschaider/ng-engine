#pragma once

#include "component.h"
#include "rigid_body.h"
#include "input_system.h"

/**
* Allows to control the velocity of the game object using buttons W, A, S, D
*/
class ControlVelocity : public Component {
public:
	/**
	* The velocity of the rigid body in horizontal direction when pressing D.
	* The negative value of this represents the velocity in horizontal direction when pressing A
	*/
	float horizontalSpeed = 0.1f;

	/**
	* The velocity of the rigid body in vertical direction when pressing W.
	* The negative value of this represents the velocity in vertical direction when pressing S
	*/
	float verticalSpeed = 0.0f;

	void fixedUpdate() override;
};