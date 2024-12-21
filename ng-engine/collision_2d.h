#pragma once

#include "collider_2d.h"
#include "vector2.h"

typedef struct Collision2D_Struct {
	Collider2D* colliderA;
	Collider2D* colliderB;
	float depth;
	Vector2 normal;
	//Vector2 contacts[];
} Collision2D;