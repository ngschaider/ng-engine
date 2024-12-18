#pragma once

#include "vector2i.h"
#include "matrix4x4.h"
#include "component.h"
#include "color.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RenderSystem : public Component {
public:
	GLFWwindow* window;
	RenderSystem();
	virtual ~RenderSystem(); // always define destructors as virtual

	Color backgroundColor = Color::green();

	void update();
	Vector2i size();
	float ratio();
	Matrix4x4 getScreenToClipMatrix();
	Matrix4x4 getClipToScreenMatrix();
};