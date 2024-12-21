#pragma once

#include "component.h"
#include <vector>
#include "collider_2d.h"
#include "collision_2d.h"

class CollisionSystem : public Component {
private:
	std::vector<Collision2D*> currentCollisions;
	void detectCollisions();
	void resolveCollision(Collision2D*);
public:
	void update();
};