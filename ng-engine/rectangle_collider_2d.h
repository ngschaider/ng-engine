#pragma once

#include "polygon_collider_2d.h"
#include "polygon_2d.h"
#include "rect.h"

class RectangleCollider2D : PolygonCollider2D {
public:
	Rect rect;
	Polygon2D getLocalPolygon();
};