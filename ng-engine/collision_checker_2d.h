#pragma once

#include "vector2.h"
#include "collider_2d.h"
#include <exception>
#include <tuple>
#include "polygon_2d.h"
#include "collision_2d.h"
#include "collision_test_result.h"

class CollisionChecker2D {
private:
	static std::pair<float, float> projectCircle(Vector2 circleCenter, float circleRadius, Vector2 axis);

	static bool areRectsIntersecting(Rect rect1, Rect rect2);
	static CollisionTestResult circleCircle(Vector2 center1, float radius1, Vector2 center2, float radius2);
	static CollisionTestResult polygonPolygon(Polygon2D polygonA, Polygon2D polygonB);
	static CollisionTestResult circlePolygon(Vector2 circleCenter, float circleRadius, Polygon2D polygon);
public:
	/**
	* Checks if two colliders are colliding.
	* Returns a collision if the two colliders are colliding, nullptr otherwise.
	* The caller takes ownership of the optionally returned instance.
	*/
	static Collision2D* checkCollision(Collider2D* colliderA, Collider2D* colliderB);
};