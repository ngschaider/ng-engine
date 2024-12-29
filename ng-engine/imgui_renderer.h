#pragma once

#include "renderer.h"

/**
* Integrates ImGui. This component is required inside the scene when using any components relying on ImGui (for example any windows or the Debug class)
*/
class ImGuiRenderer : public Renderer {
public:
	/**
	* The before render signal of the render system. Sets up a new frame
	*/
	void beforeRender() override;

	/**
	* The after render signal of the render system. Draws the current frame.
	*/
	void afterRender() override;

	/**
	* Sets up the ImGui Context
	*/
	void started() override;

	/**
	* Destructs the ImGui Context
	*/
	void stopped() override;
};