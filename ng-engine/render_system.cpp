#include "render_system.h"
#include "opengl.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

RenderSystem::RenderSystem() {
	this->graphics = new OpenGL();
}

RenderSystem::~RenderSystem() {
	if (this->graphics != nullptr) {
		delete this->graphics;
	}
}

void RenderSystem::update() {
	std::cout << "\x1B[2J\x1B[H"; // this clears the console

	this->graphics->startOfFrame();

	this->graphics->fillColor = Color::white();
	this->graphics->strokeColor = Color::white();
	this->graphics->setTransformationMatrix(Matrix4x4::identity());
	this->graphics->rectangle();

	this->graphics->endOfFrame();
}