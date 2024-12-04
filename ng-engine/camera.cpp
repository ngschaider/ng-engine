#include "camera.h"
#include "transform.h"
#include "render_system.h"
#include "scene.h"
#include <exception>

Camera::Camera() {

}

Matrix4x4 Camera::getWorldToCameraMatrix() {
	return this->transform()->getLocalToWorldMatrix().invert();
}

Matrix4x4 Camera::getCameraToWorldMatrix() {
	return this->getWorldToCameraMatrix().invert();
}

Matrix4x4 Camera::getCameraToClipMatrix() {
	RenderSystem* renderSystem = this->scene()->getComponent<RenderSystem>();
	if (renderSystem == nullptr) throw std::exception("Missing RenderSystem.");

	// scales from camera (e.g. 20x20) to clip space (-1, 1)
	Matrix4x4 scaleDown = Matrix4x4::scale(Vector3(2 / this->size.x(), 2 / this->size.y(), 1.0f));

	// make the scene appear distorted when in the clip space as it later gets stretched into screen space (from size 1,1 to 1920,1080)
	// this creates black bars but ensures, that we exactly see the region captured by the camera
	float ratio = renderSystem->graphics->ratio();
	float factorX = ratio > 1 ? ratio : 1;
	float factorY = ratio < 1 ? ratio : 1;
	Matrix4x4 distort = Matrix4x4::scale(Vector3(1 / factorX, 1 / factorY, 1.0f));

	return scaleDown * distort;
}

Matrix4x4 Camera::getClipToCameraMatrix() {
	return this->getCameraToClipMatrix().invert();
}