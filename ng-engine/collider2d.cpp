#pragma once
#include "collider2d.h"
#include "rect.h"
#include <exception>
#include "matrix4x4.h"
#include "transform.h"
#include "vector4.h"

Rect Collider2D::getLocalBounds() {
	throw new std::exception("Collider2D::getLocalBounds has to be overwritten in child classes.");
}

Rect Collider2D::getGlobalBounds() {
	Rect local = this->getLocalBounds();
	Matrix4x4 m = this->transform()->getLocalToWorldMatrix();


	Vector2 min = (m * local.bottomLeft().toVector4(0, 0)).xy();
	Vector2 max = (m * local.topRight().toVector4(0, 0)).xy();
	Vector2 size = max - min;

	return Rect(min, size, AnchorPoint::BottomLeft);
}



