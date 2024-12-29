#pragma once

#include "component.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vector2.h"
#include <map>

/**
* The input system provides provides multiple ways for getting information about input devices.
* This includes the current state of keys (keyboard + mouse), if those keys were pressed/released since the last update cycle and the current cursor position.
*/
class InputSystem : public Component {
private:
	/**
	* Returns a handle to the current window of the rendering system
	*/
	GLFWwindow* getWindow();

	/**
	* Holds the mouse's key states saved in earlyUpdate of the current update cycle
	*/
	std::map<unsigned int, bool> currentMouseStates;

	/**
	* Holds the mouse's key states saved in earlyUpdate of the last update cycle
	*/
	std::map<unsigned int, bool> previousMouseStates;

	/**
	* Holds the keyboard's key states saved in earlyUpdate of the current update cycle
	*/
	std::map<unsigned int, bool> currentKeyStates;

	/**
	* Holds the keyboard's key states saved in earlyUpdate of the last update cycle
	*/
	std::map<unsigned int, bool> previousKeyStates;

	/**
	* Returns the keyboard's current key states
	*/
	std::map<unsigned int, bool> getKeyStates();

	/**
	* Returns the mouse's current key states
	*/
	std::map<unsigned int, bool> getMouseStates();
public:
	void earlyUpdate() override;

	/**
	* Returns if the specified keyboard button is currently pressed
	*/
	bool isButtonPressed(unsigned int);

	/**
	* Returns if the specified keyboard button has just been pressed (is now pressed and was released during the last cycle)
	*/
	bool isButtonJustPressed(unsigned int);

	/**
	* Returns if the specified keyboard button has just been released (is now released and was pressed during the last cycle)
	*/
	bool isButtonJustReleased(unsigned int);

	/**
	* Returns if the specified mouse button is currently pressed
	*/
	bool isMousePressed(unsigned int);

	/**
	* Returns if the specified mouse button has just been pressed (is now pressed and was released during the last cycle)
	*/
	bool isMouseJustPressed(unsigned int);

	/**
	* Returns if the specified mouse button has just been released (is now released and was pressed during the last cycle)
	*/
	bool isMouseJustReleased(unsigned int);

	/**
	* Returns the cursor's current position in screen space.
	*/
	Vector2 getCursorPosition();
};