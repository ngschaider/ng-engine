#pragma once

#include "vector2.h"

/**
* This is the result returned from CollisionChecker2D
*/
typedef struct {
	bool colliding; // Wether the two tested geometries are colliding 
	float depth; // The depth at which the colliders are intersecting with each other
	Vector2 normal; // A normalized vector, representing the direction in which the objects have to get moved by the collision depth to not further collide.
} CollisionTestResult;