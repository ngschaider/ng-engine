#pragma once

#include "matrix4x4.h"
#include "color.h"

class Graphics {
public:
	Color fillColor = Color::white();
	Color strokeColor = Color::white();
	Color backgroundColor = Color::blue();
	int lineWidth = 1;
	Graphics();
	virtual void clear();
	virtual void setTransformationMatrix(Matrix4x4);
	virtual void startOfFrame();
	virtual void endOfFrame();
	virtual void triangle();
	virtual void rectangle();
};