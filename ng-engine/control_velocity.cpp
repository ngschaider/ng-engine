#include <cassert>
#include "control_velocity.h"
#include "game_object.h"
#include "GLFW/glfw3.h"
#include "input_system.h"
#include "rigid_body.h"
#include "scene.h"
#include "vector3.h"

void ControlVelocity::fixedUpdate() {
	RigidBody* rb = this->gameObject->getComponent<RigidBody>();
	assert(rb != nullptr);

	InputSystem* inputSystem = this->gameObject->scene->getComponent<InputSystem>();
	assert(inputSystem != nullptr);

	Vector3 v = Vector3(0, 0, 0);

	if (inputSystem->isButtonPressed(GLFW_KEY_W)) {
		v = v + Vector3(0, 1, 0) * this->verticalSpeed;
	}
	if (inputSystem->isButtonPressed(GLFW_KEY_A)) {
		v = v + Vector3(-1, 0, 0) * this->horizontalSpeed;
	}
	if (inputSystem->isButtonPressed(GLFW_KEY_S)) {
		v = v + Vector3(0, -1, 0) * this->verticalSpeed;
	}
	if (inputSystem->isButtonPressed(GLFW_KEY_D)) {
		v = v + Vector3(1, 0, 0) * this->horizontalSpeed;
	}

	rb->linearVelocity = v;
}