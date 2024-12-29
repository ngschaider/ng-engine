#pragma once

#include "renderer.h"

/**
* The menu bar allows the user to exit the application and also displays the current framerate.
*/
class MenuBar : public Renderer {
public:
	/**
	* The render signal of the render system. Renders the menu bar.
	*/
	void render() override;
};