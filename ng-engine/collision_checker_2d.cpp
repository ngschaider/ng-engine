#include "collision_checker_2d.h"
#include "collision_2d.h"
#include "rectangle_collider_2d.h"
#include "circle_collider_2d.h"
#include "polygon_collider_2d.h"
#include <algorithm>


bool CollisionChecker2D::areRectsIntersecting(Rect rect1, Rect rect2) {
	if (rect1.right() < rect2.left()) return false;
	if (rect1.bottom() < rect2.top()) return false;
	if (rect1.top() > rect2.bottom()) return false;
	if (rect1.left() > rect2.right()) return false;

	return true;
}

CollisionTestResult CollisionChecker2D::circleCircle(Vector2 center1, float radius1, Vector2 center2, float radius2) {
	float distance = center1.distance(center2);
	float radii = radius1 + radius2;

	Vector2 normal = distance == 0 ? Vector2(0, -1) : center2 - center1;

	if (distance < radii) {
		CollisionTestResult a = {
			true, // success
			radii - distance, // depth
			normal, // normal
		};
	}
	else {
		return {
			false, // success
			0, // depth
			Vector2(0, 0), // normal
		};
	}
}

CollisionTestResult CollisionChecker2D::polygonPolygon(Polygon2D polygonA, Polygon2D polygonB) {
	// get all normals
	std::vector<Vector2> normals;
	for (Vector2 edge : polygonA.getEdges()) {
		normals.push_back(edge.normal());
	}
	for (Vector2 edge : polygonB.getEdges()) {
		normals.push_back(edge.normal());
	}

	// use the normal vectors as an axis, project all vertices and see if there is a gap
	Vector2 resolutionNormal = Vector2(0, 0);
	float minDepth = INFINITY;
	for (Vector2 axis : normals) {
		std::vector<float> projectionA = polygonA.project(axis);
		std::pair<std::vector<float>::iterator, std::vector<float>::iterator> boundsA = std::minmax_element(projectionA.begin(), projectionA.end());
		float minA = *boundsA.first;
		float maxA = *boundsA.second;


		std::vector<float> projectionB = polygonB.project(axis);
		std::pair<std::vector<float>::iterator, std::vector<float>::iterator> boundsB = std::minmax_element(projectionB.begin(), projectionB.end());
		float minB = *boundsB.first;
		float maxB = *boundsB.second;

		if (minA >= maxB || minB >= maxA) {
			// we have a gap
			return {
				false, // success
				0, // depth
				Vector2(0, 0), // normal
			};
		}

		float axisDepth = std::min(maxB - minA, maxA - minB);
		if (axisDepth < minDepth) {
			resolutionNormal = axis;
			minDepth = axisDepth;
		}
	}

	Vector2 centerA = polygonA.getArithmeticMean();
	Vector2 centerB = polygonB.getArithmeticMean();

	Vector2 dir = centerB - centerA;

	if (dir.dot(resolutionNormal) < 0) {
		resolutionNormal = resolutionNormal * -1;
	}

	return {
		true, // success
		minDepth, // depth
		resolutionNormal, // normal
	};
}

CollisionTestResult CollisionChecker2D::circlePolygon(Vector2 circleCenter, float circleRadius, Polygon2D polygon) {
	// get all normals
	std::vector<Vector2> normals;
	for (Vector2 edge : polygon.getEdges()) {
		normals.push_back(edge.normal());
	}

	// use the normal vectors as an axis, project all vertices and see if there is a gap
	Vector2 resolutionNormal = Vector2(0, 0);
	float minDepth = INFINITY;
	for (Vector2 axis : normals) {
		std::pair<float, float> boundsA = CollisionChecker2D::projectCircle(circleCenter, circleRadius, axis);
		float minA = boundsA.first;
		float maxA = boundsA.second;


		std::vector<float> projection = polygon.project(axis);
		std::pair<std::vector<float>::iterator, std::vector<float>::iterator> boundsB = std::minmax_element(projection.begin(), projection.end());
		float minB = *boundsB.first;
		float maxB = *boundsB.second;

		if (minA >= maxB || minB >= maxA) {
			// we have a gap
			return {
				false, // success
				0, // depth
				Vector2(0, 0), // normal
			};
		}

		float axisDepth = std::min(maxB - minA, maxA - minB);
		if (axisDepth < minDepth) {
			resolutionNormal = axis;
			minDepth = axisDepth;
		}
	}

	Vector2 dir = polygon.getArithmeticMean() - circleCenter;

	if (dir.dot(resolutionNormal) < 0) {
		resolutionNormal = resolutionNormal * -1;
	}

	return {
		true, // success
		minDepth, // depth
		resolutionNormal, // normal
	};
}

std::pair<float, float> CollisionChecker2D::projectCircle(Vector2 circleCenter, float circleRadius, Vector2 axis) {
	Vector2 p1 = circleCenter - axis * circleRadius;
	Vector2 p2 = circleCenter + axis * circleRadius;

	float min = p1.dot(axis);
	float max = p2.dot(axis);

	if (min >= max) {
		throw new std::exception("Should this be swapped?");
	}

	return std::make_pair(min, max);
}

Collision2D* CollisionChecker2D::checkCollision(Collider2D* colliderA, Collider2D* colliderB) {
	Rect rectA = colliderA->getGlobalBounds();
	Rect rectB = colliderB->getGlobalBounds();

	if (!CollisionChecker2D::areRectsIntersecting(rectA, rectB)) {
		return nullptr;
	}

	CircleCollider2D* circleColliderA = dynamic_cast<CircleCollider2D*>(colliderA);
	CircleCollider2D* circleColliderB = dynamic_cast<CircleCollider2D*>(colliderB);
	PolygonCollider2D* polygonColliderA = dynamic_cast<PolygonCollider2D*>(colliderA);
	PolygonCollider2D* polygonColliderB = dynamic_cast<PolygonCollider2D*>(colliderB);

	if (circleColliderA != nullptr && circleColliderB != nullptr) {
		CollisionTestResult result = CollisionChecker2D::circleCircle(circleColliderA->getWorldPosition(), circleColliderA->getWorldRadius(),
			circleColliderB->getWorldPosition(), circleColliderB->getWorldRadius());

		if (!result.colliding) return nullptr;

		return new Collision2D({
			colliderA,
			colliderB,
			result.depth,
			result.normal,
			});
	}
	else if (circleColliderA != nullptr && polygonColliderB != nullptr) {
		CollisionTestResult result = CollisionChecker2D::circlePolygon(circleColliderA->getWorldPosition(),
			circleColliderA->getWorldRadius(), polygonColliderB->getWorldPolygon());

		if (!result.colliding) return nullptr;

		return new Collision2D({
			colliderA,
			colliderB,
			result.depth,
			result.normal,
			});
	}
	else if (polygonColliderA != nullptr && circleColliderB != nullptr) {
		CollisionTestResult result = CollisionChecker2D::circlePolygon(circleColliderB->getWorldPosition(),
			circleColliderB->getWorldRadius(), polygonColliderA->getWorldPolygon());

		if (!result.colliding) return nullptr;

		return new Collision2D({
			colliderA,
			colliderB,
			result.depth,
			result.normal,
			});
	}
	else if (polygonColliderA != nullptr && polygonColliderB != nullptr) {
		CollisionTestResult result = CollisionChecker2D::polygonPolygon(polygonColliderA->getWorldPolygon(), polygonColliderB->getWorldPolygon());

		if (!result.colliding) return nullptr;

		return new Collision2D({
			colliderA,
			colliderB,
			result.depth,
			result.normal,
			});
	}
}