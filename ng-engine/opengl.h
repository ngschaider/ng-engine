#pragma once

#include "graphics.h"
#include "color.h"
#include <vector>
#include "vector3.h"
#include "matrix4x4.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGL : public Graphics {
private:
	GLuint positionBuffer;
	unsigned int positionLoc;
	unsigned int colorLoc;
	unsigned int matrixLoc;
	void draw(std::vector<Vector3>, GLenum);
	GLFWwindow* window;
public:
	OpenGL();
	~OpenGL();
	void clear();
	void setTransformationMatrix(Matrix4x4);
	void startOfFrame();
	void endOfFrame();
	void triangle();
	void rectangle();
};