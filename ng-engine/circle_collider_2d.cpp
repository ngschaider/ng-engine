#include "circle_collider_2d.h"
#include "transform.h"
#include "matrix4x4.h"

Vector2 CircleCollider2D::getWorldPosition() {
	return this->transform()->localToWorld(this->localPosition);
}

float CircleCollider2D::getWorldRadius() {
	return this->transform()->localToWorld(this->localRadius);
}

Rect CircleCollider2D::getLocalBounds() {
	return Rect(this->localPosition, Vector2(this->localRadius * 2, this->localRadius * 2), AnchorPoint::CenterCenter);
}