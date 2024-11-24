#pragma once

#include "graphics.h"
#include "color.h"
#include <vector>

class OpenGL : public Graphics {
private:
	unsigned int positionBuffer;
	unsigned int positionLoc;
	unsigned int colorLoc;
	unsigned int matrixLoc;
	void draw(std::vector<Vector3>, unsigned int primitive);
	
public:
	Color fillColor;
	Color strokeColor;
	int lineWidth;
	OpenGL();
	~OpenGL();
};