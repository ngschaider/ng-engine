#pragma once

#include "vector2i.h"
#include "matrix4x4.h"
#include "component.h"
#include "color.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
* The rendering system is responsible for rendering the scene to the screen.
* It is most likely used as a singleton component and it does not matter to which game object it is attached to.
* It sets up a window and a rendering context on construction and renders the scene to the screen in the late update.
* The render cycle is as follows
* 1. The window is cleared using the background color
* 2. beforeRender is called on all renderer components
* 3. render is called on all renderer components
* 4. afterRender is called on all renderer components
* 5. The rendered image is swapped with the front buffer
*/
class RenderSystem : public Component {
public:
	/**
	* The handle to the constructed window. This should only be written to by the rendering system.
	* TODO: Make this read only by making it private and providing a getter method.
	*/
	GLFWwindow* window;

	RenderSystem();
	virtual ~RenderSystem(); // always define destructors as virtual

	/**
	* The background color of the window.
	*/
	Color backgroundColor = Color::black();

	/**
	* Overwritten method from Component. This is where the rendering takes place
	*/
	void lateUpdate() override;

	/**
	* Returns the size of the window in pixels
	*/
	Vector2i size();

	/**
	* Returns the aspect ratio of the window
	*/
	float ratio();

	/**
	* Returns the transformation matrix that transforms coordinates from screen space to clip space
	*/
	Matrix4x4 getScreenToClipMatrix();

	/**
	* Returns the transformation matrix that transforms coordinates from clip space to screen space
	*/
	Matrix4x4 getClipToScreenMatrix();

	/**
	* Transforms the given coordinates from screen space to clip space
	*/
	Vector2 screenToClip(Vector2 screen);

	/**
	* Transforms the given coordinates from clip space to screen space
	*/
	Vector2 clipToScreen(Vector2 clip);
};