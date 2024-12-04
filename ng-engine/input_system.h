#pragma once

#include "component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vector2.h"

class InputSystem : public Component {
private:
	GLFWwindow* getWindow();
public:
	InputSystem();
	void update();
	bool isButtonPressed(int);
	bool isMousePressed(int);
	Vector2 getCursorPosition();
};