#pragma once

#include "component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vector2.h"
#include <map>

class InputSystem : public Component {
private:
	GLFWwindow* getWindow();
	std::map<unsigned int, bool> currentMouseStates;
	std::map<unsigned int, bool> previousMouseStates;
	std::map<unsigned int, bool> currentKeyStates;
	std::map<unsigned int, bool> previousKeyStates;
	std::map<unsigned int, bool> getKeyStates();
	std::map<unsigned int, bool> getMouseStates();
public:
	InputSystem();
	void earlyUpdate() override;
	bool isButtonPressed(unsigned int);
	bool isButtonJustPressed(unsigned int);
	bool isButtonJustReleased(unsigned int);
	bool isMousePressed(unsigned int);
	bool isMouseJustPressed(unsigned int);
	bool isMouseJustReleased(unsigned int);
	Vector2 getCursorPosition();
};