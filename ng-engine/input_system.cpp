#include "input_system.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "scene.h"
#include "render_system.h"
#include <exception>
#include "vector2.h"

InputSystem::InputSystem() {

}

std::map<unsigned int, bool> InputSystem::getKeyStates() {
	std::map<unsigned int, bool> states;
	GLFWwindow* window = this->getWindow();

	states[32] = glfwGetKey(window, 32);
	states[39] = glfwGetKey(window, 39);

	for (int i = 44; i <= 57; i++) {
		states[i] = glfwGetKey(window, i);
	}

	states[59] = glfwGetKey(window, 59);
	states[61] = glfwGetKey(window, 61);

	for (int i = 61; i <= 93; i++) {
		states[i] = glfwGetKey(window, i);
	}

	states[96] = glfwGetKey(window, 96);
	states[161] = glfwGetKey(window, 161);
	states[162] = glfwGetKey(window, 162);

	for (int i = 256; i <= 269; i++) {
		states[i] = glfwGetKey(window, i);
	}
	for (int i = 280; i <= 284; i++) {
		states[i] = glfwGetKey(window, i);
	}
	for (int i = 290; i <= 314; i++) {
		states[i] = glfwGetKey(window, i);
	}
	for (int i = 320; i <= 336; i++) {
		states[i] = glfwGetKey(window, i);
	}
	for (int i = 340; i <= 348; i++) {
		states[i] = glfwGetKey(window, i);
	}

	return states;
}

std::map<unsigned int, bool> InputSystem::getMouseStates() {
	std::map<unsigned int, bool> states;
	GLFWwindow* window = this->getWindow();

	for (int i = 0; i <= 7; i++) {
		this->previousMouseStates[i] = glfwGetMouseButton(window, i);
	}

	return states;
}

void InputSystem::earlyUpdate() {
	this->previousKeyStates = this->currentKeyStates;
	this->previousMouseStates = this->currentMouseStates;

	this->currentKeyStates = this->getKeyStates();
	this->currentMouseStates = this->getMouseStates();
}

GLFWwindow* InputSystem::getWindow() {
	RenderSystem* renderSystem = this->scene()->getComponent<RenderSystem>();
	if (renderSystem == nullptr) throw new std::exception("InputSystem requires RenderSystem.");

	if (renderSystem->window == nullptr) throw new std::exception("InputSystem requires a GLFW window to be established.");

	return renderSystem->window;
}

bool InputSystem::isButtonPressed(unsigned int button) {
	return this->currentKeyStates[button];
}

bool InputSystem::isButtonJustPressed(unsigned int button) {
	if (this->isButtonPressed(button)) {
		this->previousKeyStates[button];
	}
	return !this->previousKeyStates[button] && this->isButtonPressed(button);
}

bool InputSystem::isButtonJustReleased(unsigned int button) {
	return this->previousKeyStates[button] && !this->isButtonPressed(button);
}

bool InputSystem::isMousePressed(unsigned int button) {
	return previousKeyStates[button];
}

bool InputSystem::isMouseJustPressed(unsigned int button) {
	return !this->previousMouseStates[button] && this->isMousePressed(button);
}

bool InputSystem::isMouseJustReleased(unsigned int button) {
	return this->previousMouseStates[button] && !this->isMousePressed(button);
}

Vector2 InputSystem::getCursorPosition() {
	GLFWwindow* window = this->getWindow();
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	return Vector2((float) x, (float) y);
}