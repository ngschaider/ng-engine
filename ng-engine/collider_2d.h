#pragma once

#include "component.h"
#include "rect.h"
#include "event.h"
#include "collider_2d.h"
#include "renderer.h"
#include "line_renderer.h"

class Collider2D : public Renderer {
private:
	unsigned int VAO;
public:
	Collider2D();

	/**
	* If true, the axis-aligned bounding box of this collider will be drawn
	*/
	bool drawAABB = true;

	/**
	* Emitted by the collision system whenever a new collision starts
	*/
	Event<Collider2D*> onCollisionStart;

	/**
	* Emitted by the collision system whenever an existing collision ends
	*/
	Event<Collider2D*> onCollisionEnd;

	/**
	* Contains all colliders this collider is currently colliding with.
	* This should not be edited outside of Collider2D.
	*/
	std::vector<Collider2D*> collidingWith;

	/**
	* Emitted by the collision system on each update cycle for each collision this collider is part of.
	*/
	Event<Collider2D*> onColliding;
	virtual Rect getLocalBounds();
	Rect getWorldBounds();
	void render();
};
