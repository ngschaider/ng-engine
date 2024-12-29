#pragma once

#include "collider_2d.h"
#include "vector2.h"

/**
* Represents a collision
*/
typedef struct {
	Collider2D* colliderA; // First collider of the collision
	Collider2D* colliderB; // Second collider of the collision
	float depth; // The depth at which the colliders are intersecting with each other
	Vector2 normal; // A normalized vector, representing the direction in which the objects have to get moved by the collision depth to not further collide.
	// Vector2 contacts[]; // The contact points between the colliders
} Collision2D;