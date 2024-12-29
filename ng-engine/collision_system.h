#pragma once

#include "component.h"
#include <vector>
#include "collider_2d.h"
#include "collision_2d.h"

/**
* The collision system regularly checks if any colliders are intersecting and emits the events "onCollisionStart", "onColliding" and "onCollisionEnd" if necessary.
* If two colliders are intersecting and rigid bodies are attached to the collider's game objects, it will try to resolve the collision
* while also respecting the rigid bodies properties like mass and restitution.
*/
class CollisionSystem : public Component {
private:
	/**
	* Detects all collisions between colliders in the scene
	* Updates the currentCollisions list
	*/
	void detectCollisions();

	/**
	* Tries to resolve a collision by moving the game objects apart, while respecting rigid body properties
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