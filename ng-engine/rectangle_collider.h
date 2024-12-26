#pragma once

#include "polygon_collider_2d.h"
#include "polygon_2d.h"
#include "rect.h"

class RectangleCollider : public PolygonCollider2D {
public:
	Rect rect = Rect(Vector2(0, 0), Vector2(1, 1), AnchorPoint::CenterCenter);
	Polygon2D getLocalPolygon();
	RectangleCollider();
};