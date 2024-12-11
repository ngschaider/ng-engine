#include "control_velocity.h"
#include "game_object.h"
#include "rigid_body.h"
#include "scene.h"
#include "vector3.h"

ControlVelocity::ControlVelocity() {

}

void ControlVelocity::update() {
	RigidBody* rb = this->gameObject->getComponent<RigidBody>();
	if (rb == nullptr) {
		throw new std::exception("ControlVelocity requires a RigidBody component on the same GameObject.");
	}

	InputSystem* inputSystem = this->gameObject->scene->getComponent<InputSystem>();
	if (inputSystem == nullptr) {
		throw new std::exception("ControlVelocity requires a InputSystem component in the same scene.");
	}

	Vector3 velocity = Vector3(0, 0, 0);

	if (inputSystem->isButtonPressed(GLFW_KEY_W)) {
		velocity = velocity + Vector3(0, 1, 0);
	}
	if (inputSystem->isButtonPressed(GLFW_KEY_A)) {
		velocity = velocity + Vector3(-1, 0, 0);
	}
	if (inputSystem->isButtonPressed(GLFW_KEY_S)) {
		velocity = velocity + Vector3(0, -1, 0);
	}
	if (inputSystem->isButtonPressed(GLFW_KEY_D)) {
		velocity = velocity + Vector3(1, 0, 0);
	}
	if (inputSystem->isButtonPressed(GLFW_KEY_Q)) {
		velocity = velocity + Vector3(0, 0, 1);
	}
	if (inputSystem->isButtonPressed(GLFW_KEY_E)) {
		velocity = velocity + Vector3(0, 0, -1);
	}

	rb->linearVelocity = velocity * 0.01f;
}