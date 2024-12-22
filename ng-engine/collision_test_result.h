#pragma once

#include "vector2.h"

typedef struct {
	bool colliding;
	float depth;
	Vector2 normal;
} CollisionTestResult;