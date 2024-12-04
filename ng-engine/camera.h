#pragma once

#include "component.h"
#include "matrix4x4.h"

class Camera : public Component {
public:
	Vector2 size = Vector2(20, 20);
	bool isActive = true;
	Camera();
	Matrix4x4 getWorldToCameraMatrix();
	Matrix4x4 getCameraToWorldMatrix();
	Matrix4x4 getCameraToClipMatrix();
	Matrix4x4 getClipToCameraMatrix();
};