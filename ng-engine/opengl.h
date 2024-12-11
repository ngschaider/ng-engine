#pragma once

#include "graphics.h"
#include "color.h"
#include "shader.h"
#include <vector>
#include "vector3.h"
#include "matrix4x4.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>

struct Character {
	unsigned int textureId; // id handle of the glyph texture
	Vector2 size = Vector2(0, 0); // size of glyph
	Vector2 bearing = Vector2(0, 0); // offset from baseline to left/top of glyph
	unsigned int advance; // offset to advance to next glyph
};

class OpenGL : public Graphics {
private:
	GLuint vertexBuffer;
	Shader* textShader;
	Shader* solidShader;
	std::map<char, Character> characters;
	void draw(std::vector<Vector3>, GLenum);
	Matrix4x4 transformationMatrix = Matrix4x4::identity();
public:
	GLFWwindow* window;
	OpenGL();
	virtual ~OpenGL(); // always define destructors as virtual
	Vector2 size();
	void clear();
	void setTransformationMatrix(Matrix4x4);
	void startOfFrame();
	void endOfFrame();
	void triangle();
	void rectangle();
	void text(std::string);
	Matrix4x4 getScreenToClipMatrix();
	Matrix4x4 getClipToScreenMatrix();
};