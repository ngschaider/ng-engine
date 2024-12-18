#include "input_system.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "scene.h"
#include "render_system.h"
#include <exception>
#include "vector2.h"

InputSystem::InputSystem() {

}

GLFWwindow* InputSystem::getWindow() {
	RenderSystem* renderSystem = this->scene()->getComponent<RenderSystem>();
	if (renderSystem == nullptr) throw new std::exception("InputSystem requires RenderSystem.");

	if (renderSystem->window == nullptr) throw new std::exception("InputSystem requires a GLFW window to be established.");

	return renderSystem->window;
}

void InputSystem::update() {
	
}

bool InputSystem::isButtonPressed(int button) {
	GLFWwindow* window = this->getWindow();
	return glfwGetKey(window, button) == GLFW_PRESS;
}

bool InputSystem::isMousePressed(int button) {
	GLFWwindow* window = this->getWindow();
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

Vector2 InputSystem::getCursorPosition() {
	GLFWwindow* window = this->getWindow();
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	return Vector2((float) x, (float) y);
}