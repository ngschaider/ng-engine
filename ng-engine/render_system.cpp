#include "render_system.h"
#include "opengl.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "game_object.h"
#include "scene.h"
#include "renderer.h"

RenderSystem::RenderSystem() {
	this->graphics = new OpenGL();
}

RenderSystem::~RenderSystem() {
	if (this->graphics != nullptr) {
		delete this->graphics;
	}
}

void RenderSystem::update() {
	this->graphics->startOfFrame();

	std::vector<Renderer*> renderers = this->gameObject->scene->getComponents<Renderer>();
	for (Renderer* renderer : renderers) {
		renderer->render(this->graphics);
	}

	this->graphics->endOfFrame();
}