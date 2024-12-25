#include "collision_visualizer.h"
#include <exception>
#include "collision_system.h"
#include "scene.h"
#include "line_renderer.h"
#include <vector>
#include "debug.h"

CollisionVisualizer::CollisionVisualizer() {
	
}

void CollisionVisualizer::update() {
	Debug* debug = this->scene()->getComponent<Debug>();
	if (debug == nullptr) throw new std::exception();

	CollisionSystem* collisionSystem = this->scene()->getComponent<CollisionSystem>();
	if (collisionSystem == nullptr) throw new std::exception();

	for (Collision2D* collision : collisionSystem->currentCollisions) {
		Vector3 start = collision->colliderA->transform()->position;
		Vector3 end = start + collision->normal.normalized().toVector3(0) * 1;
		debug->line(start, end, Color::black());
	}
}