#pragma once

#include "component.h"
#include <vector>
#include "collider_2d.h"
#include "collision_2d.h"

class CollisionSystem : public Component {
private:
	/**
	* Detects all collisions between colliders in the scene
	* Updates the currentCollisions list
	*/
	void detectCollisions();

	/**
	* Tries to resolve a collision by moving the game objects apart
	*/
	void resolveCollision(Collision2D*);
public:
	/**
	* A list containing all currently active collisions
	* This should only be edited by the collision system itself.
	*/
	std::vector<Collision2D*> currentCollisions;

	void update() override;
};