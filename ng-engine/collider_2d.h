#pragma once

#include "component.h"
#include "rect.h"
#include "event.h"
#include "collider_2d.h"
#include "renderer.h"
#include "line_renderer.h"

/**
* Collider base class. Colliders used have to inherit this and implement "getLocalBounds".
* Note that the default collision system only supports CircleCollider and PolygonCollider2D.
*/
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

	/**
	* Returns the axis-aligned bounding box of the collider in local space.
	* This has to be overwritten in child classes.
	*/
	virtual Rect getLocalBounds();

	/**
	* Returns the axis-aligned bounding box of the collider in world space.
	*/
	Rect getWorldBounds();

	void render() override;
};
