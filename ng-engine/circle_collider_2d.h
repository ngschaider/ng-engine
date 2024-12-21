#pragma once

#include "collider_2d.h"
#include "rect.h"
#include "vector2.h"

class CircleCollider2D : Collider2D {
public:
	/**
	* An additional positional offset of the collider
	*/
	Vector2 localPosition = Vector2(0, 0);

	/**
	* The radius of the circle defining the collider
	*/
	float localRadius = 0.5f;

	/**
	* Returns the position of the collider in world space
	*/
	Vector2 getWorldPosition();

	/**
	* Returns the radius of the collider in world space
	*/
	float getWorldRadius();

	/**
	* Returns the bounds of the collider in local space
	*/
	Rect getLocalBounds();
};