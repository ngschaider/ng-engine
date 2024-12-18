#pragma once

#include "renderer.h"

class ImGuiRenderer : public Renderer {
public:
	ImGuiRenderer();
	~ImGuiRenderer();
	void beforeRender(); // called on every renderer instance after clearing the framebuffer
	void render(); // called on every renderer instance after the before-render cycle
	void afterRender(); // called on every renderer instance after the render cycle
	void started();
	void stopped();
};