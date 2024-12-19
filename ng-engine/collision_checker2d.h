#pragma once

#include "vector2.h"
#include "collider2d.h"
#include <exception>
#include <tuple>

class CollisionChecker2D {
private:
	static std::tuple<float, float> projectCircle(Vector2 circleCenter, float circleRadius, Vector2 axis) {
		Vector2 p1 = circleCenter - axis * circleRadius;
		Vector2 p2 = circleCenter + axis * circleRadius;

		float min = p1.dot(axis);
		float max = p2.dot(axis);

		if (min >= max) {
			throw new std::exception("Should this be swapped?");
		}

		return std::make_tuple(min, max);
	}
public:
	static void checkCollision(Collider2D bodyA, Collider2D bodyB);
};