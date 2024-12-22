#pragma once

#include "collider_2d.h"
#include "polygon_2d.h"

class PolygonCollider2D : public Collider2D {
public:
	Rect getLocalBounds();
	virtual Polygon2D getLocalPolygon();
	Polygon2D getWorldPolygon();
};