#pragma once

#include "renderer.h"

class ImGuiRenderer : public Renderer {
public:
	ImGuiRenderer();
	~ImGuiRenderer();
	void beforeRender() override; // called on every renderer instance after clearing the framebuffer
	void render() override; // called on every renderer instance after the before-render cycle
	void afterRender() override; // called on every renderer instance after the render cycle

	void started() override;
	void stopped() override;
};