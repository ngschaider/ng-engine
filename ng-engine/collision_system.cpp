#include "collision_system.h"
#include "scene.h"
#include "collider_2d.h"
#include "collision_2d.h"
#include "collision_checker_2d.h"
#include <assert.h>
#include "rigid_body.h"
#include <math.h>
#include "event.h"

template class Event<Collider2D*>;

void CollisionSystem::update() {
	this->detectCollisions();

	for (Collision2D* collision : this->currentCollisions) {
		this->resolveCollision(collision);
	}
}

// FIXME: If the component is removed from the scene while it is colliding, 
// the onCollisionEnd callback will never be triggered
void CollisionSystem::detectCollisions() {
	std::vector<Collider2D*> colliders = this->scene()->getComponents<Collider2D>();

	// generate the pairs of colliders between which collision should be checked
	std::vector<std::pair<Collider2D*, Collider2D*>> pairs;
	for (int i = 0; i < colliders.size(); i++) {
		for (int j = 0; j < colliders.size(); j++) {
			if (i <= j) continue;
			pairs.push_back(std::make_pair(colliders[i], colliders[j]));
		}
	}

	for (std::pair<Collider2D*, Collider2D*> pair : pairs) {
		Collider2D* colliderA = pair.first;
		Collider2D* colliderB = pair.second;

		// Search the list of collisions and see if there already  
		// is a collision with those colliders in the list.
		std::vector<Collision2D*>::iterator it = std::find_if(this->currentCollisions.begin(), this->currentCollisions.end(), [colliderA, colliderB](Collision2D* collision) {
			bool a = collision->colliderA == colliderA && collision->colliderB == colliderB;
			bool b = collision->colliderA == colliderB && collision->colliderB == colliderA;
			return a || b;
		});
		Collision2D* existingCollision = it != this->currentCollisions.end() ? *it : nullptr;

		// Invoke the collision checker to determine if the colidders are currently colliding
		Collision2D* collision = CollisionChecker2D::checkCollision(colliderA, colliderB);

		if (collision != nullptr) {
			// we are currently colliding
			if (existingCollision == nullptr) {
				// but we were not colliding before -> collision started

				// Save the collision for later
				this->currentCollisions.push_back(collision);

				// invoke collision start event on both colliders
				colliderA->onCollisionStart.emit(colliderB);
				colliderB->onCollisionStart.emit(colliderA);
			}

			// invoke "currently colliding" event on both colliders
			colliderA->onColliding.emit(colliderB);
			colliderB->onColliding.emit(colliderA);
		}
		else {
			// we are currently NOT colliding
			if (existingCollision != nullptr) {
				// but were colliding before

				// remove it from the list
				std::vector<Collision2D*>::iterator it = std::find(this->currentCollisions.begin(), this->currentCollisions.end(), existingCollision);
				assert(it != this->currentCollisions.end());
				this->currentCollisions.erase(it);

				// invoke collision end event on both colliders
				colliderA->onCollisionEnd.emit(colliderB);
				colliderB->onCollisionEnd.emit(colliderA);
			}
		}
	}
}

void CollisionSystem::resolveCollision(Collision2D* collision) {
	RigidBody* bodyA = collision->colliderA->gameObject->getComponent<RigidBody>();
	RigidBody* bodyB = collision->colliderB->gameObject->getComponent<RigidBody>();

	// only collisions of game objects with attached rigid bodies are resolved
	if (bodyA == nullptr || bodyB == nullptr) return;

	Vector2 relativeVelocity = bodyB->linearVelocity.xy() - bodyA->linearVelocity.xy();

	if (relativeVelocity.dot(collision->normal) > 0) {
		return;
	}

	float e = std::min(bodyA->restitution, bodyB->restitution);

	float enumerator = -(1 + e) * relativeVelocity.dot(collision->normal);
	float denominator = (1 / bodyA->mass) + (1 / bodyB->mass);
	float j = enumerator / denominator;

	bodyA->transform()->move(-collision->normal * collision->depth / 2);
	bodyB->transform()->move(collision->normal * collision->depth / 2);

	//if (bodyA->mass != INFINITY) {
	//	float factor = bodyB->mass == INFINITY ? 1.0f : 2.0f;
	//	bodyA->transform()->move(-1 * collision->normal * collision->depth / factor);
	//	Vector2 diff = bodyA->linearVelocity.xy() - collision->normal;
	//	Vector2 d = diff * j;
	//	Vector2 e = d / bodyA->mass;
	//	Vector3 linVel = e.toVector3(0);
	//	bodyA->linearVelocity = Vector3(0, 0, 0);
	//}
	//if (bodyB->mass != INFINITY) {
	//	float factor = bodyA->mass == INFINITY ? 1.0f : 2.0f;
	//	bodyB->transform()->move(collision->normal * collision->depth / factor);
	//	bodyB->linearVelocity = (bodyB->linearVelocity.xy() + collision->normal * j / bodyB->mass).toVector3(0);
	//}
}