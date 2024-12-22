#pragma once

#include "component.h"
#include "rect.h"
#include "event.h"
#include "renderer.h"

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
	Event onCollisionStart;

	/**
	* Emitted by the collision system whenever an existing collision ends
	*/
	Event onCollisionEnd;

	/**
	* Emitted by the collision system on each update cycle for each collision this collider is part of.
	*/
	Event onColliding;
	virtual Rect getLocalBounds();
	Rect getGlobalBounds();
	void render();
};
