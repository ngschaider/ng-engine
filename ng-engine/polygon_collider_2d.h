#pragma once

#include "collider_2d.h"
#include "polygon_2d.h"

class PolygonCollider2D : Collider2D {
public:
	Polygon2D getLocalPolygon();
	Polygon2D getWorldPolygon();
};