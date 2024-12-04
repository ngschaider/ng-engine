#pragma once

#include "matrix4x4.h"
#include "color.h"

class Graphics {
public:
	Color fillColor = Color::white();
	bool doFill = true;
	Color strokeColor = Color::white();
	bool doStroke = false;
	Color backgroundColor = Color::black();
	float fontSize = 1.0f;
	float lineWidth = 1.0f;

	Graphics();
	virtual Vector2 size();
	float ratio();
	virtual void clear();
	virtual void setTransformationMatrix(Matrix4x4);
	virtual void startOfFrame();
	virtual void endOfFrame();
	virtual void triangle();
	virtual void rectangle();
	Matrix4x4 getScreenToClipMatrix();
	Matrix4x4 getClipToScreenMatrix();
};