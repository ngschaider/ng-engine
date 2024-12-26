#include "circle_collider.h"
#include "transform.h"
#include "matrix4x4.h"

Vector2 CircleCollider::getWorldPosition() {
	return this->transform()->localToWorld(this->localPosition);
}

float CircleCollider::getWorldRadius() {
	return this->transform()->localToWorld(this->localRadius);
}

Rect CircleCollider::getLocalBounds() {
	return Rect(this->localPosition, Vector2(this->localRadius * 2, this->localRadius * 2), AnchorPoint::CenterCenter);
}