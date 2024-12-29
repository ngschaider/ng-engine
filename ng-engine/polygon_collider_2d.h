#pragma once

#include "collider_2d.h"
#include "polygon_2d.h"

/**
* A generic collider class for geometries consisting of discrete vertices (polygons)
*/
class PolygonCollider2D : public Collider2D {
public:
	/**
	* Returns the axis-aligned bounding box of the collider in local space.
	*/
	Rect getLocalBounds();

	/**
	* Returns the polygon of the collider in local space.
	* This has to be overwritten in child classes.
	*/
	virtual Polygon2D getLocalPolygon();

	/**
	* Returns the polygon of the collider in world space.
	*/
	Polygon2D getWorldPolygon();
};