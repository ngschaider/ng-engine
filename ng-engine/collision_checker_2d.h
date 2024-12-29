#pragma once

#include "vector2.h"
#include "collider_2d.h"
#include <exception>
#include <tuple>
#include "polygon_2d.h"
#include "collision_2d.h"
#include "collision_test_result.h"

/**
* A geometrical utility class for determining if and how geometries intersect
*/
class CollisionChecker2D {
private:
	/**
	* Projects a circle onto a given axis and returns the start and end of the resulting projection
	*/
	static std::pair<float, float> projectCircle(Vector2 circleCenter, float circleRadius, Vector2 axis);

	/**
	* Returns if the two given axis-aligned bounding boxes are intersecting with each other.
	* This is very useful for improving the performance of collision checks among many objects as this is very cheap compared to other methods
	* and if the AABB are not colliding, the objects themselves are for sure also not colliding!
	*/
	static bool areRectsIntersecting(Rect rect1, Rect rect2);

	/**
	* Checks if two circles are colliding
	*/
	static CollisionTestResult circleCircle(Vector2 center1, float radius1, Vector2 center2, float radius2);

	/**
	* Checks if two polygons are colliding
	*/
	static CollisionTestResult polygonPolygon(Polygon2D polygonA, Polygon2D polygonB);

	/**
	* Checks if a circle and a polygon are colliding
	*/
	static CollisionTestResult circlePolygon(Vector2 circleCenter, float circleRadius, Polygon2D polygon);

	/**
	* This class is 100% static, it should never get constructed.
	*/
	CollisionChecker2D() = delete;
public:
	/**
	* Checks if two colliders are colliding.
	* Returns a collision if the two colliders are colliding, nullptr otherwise.
	* The caller takes ownership of the optionally returned instance.
	*/
	static Collision2D* checkCollision(Collider2D* colliderA, Collider2D* colliderB);
};