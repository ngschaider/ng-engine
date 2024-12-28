#include "camera.h"
#include "transform.h"
#include "render_system.h"
#include "scene.h"
#include <exception>

Camera::Camera() {

}

float Camera::ratio() {
	return this->size.x() / this->size.y();
}

Matrix4x4 Camera::getWorldToCameraMatrix() {
	return Matrix4x4::TRS(this->transform()->position, this->transform()->rotation, Vector3(1, 1, 1)).invert();
}

Matrix4x4 Camera::getCameraToWorldMatrix() {
	return this->getWorldToCameraMatrix().invert();
}

Matrix4x4 Camera::getCameraToClipMatrix() {
	RenderSystem* renderSystem = this->scene()->getComponent<RenderSystem>();
	if (renderSystem == nullptr) throw std::exception("Missing RenderSystem.");

	// scales from camera (e.g. -10, 10) to clip space (-1, 1)
	// clip space has width=2, height=2 !!!

	float camMin = std::min(this->size.x(), this->size.y());
	float camMax = std::max(this->size.x(), this->size.y());
	float camRatio = this->ratio();
	Matrix4x4 scaleDown = Matrix4x4::scale(Vector3(2 / camMin, 2 / camMin, 1.0f));



	//Matrix4x4 scaleDown = Matrix4x4::identity();
	//if (this->ratio() > 1) {
	//	// wide camera
	//	scaleDown = Matrix4x4::scale(Vector3(2 / this->size.x() / this->ratio(), 2 / this->size.y(), 1.0f));
	//} else {
	//	// not so wide-camera
	//	scaleDown = Matrix4x4::scale(Vector3(1, this->ratio(), 1)) * Matrix4x4::scale(Vector3(2 / this->size.x(), 2 / this->size.y(), 1.0f));
	//}

	// make the scene appear distorted in clip space as it later gets stretched into screen space (from size 1,1 to 1920,1080)
	// this creates black bars but ensures, that we exactly see the region captured by the camera
	//float ratio = renderSystem->ratio();

	float screenMin = (float) std::min(renderSystem->size().x(), renderSystem->size().y());
	float screenMax = (float) std::max(renderSystem->size().x(), renderSystem->size().y());
	float screenRatio = renderSystem->ratio();
	Matrix4x4 distort = Matrix4x4::scale(Vector3(1.0f / renderSystem->size().x() * screenMin, 1.0f / renderSystem->size().y() * screenMin, 1.0f));

	//if (ratio > 1) {
	//	// wide-screen!
	//	distort = Matrix4x4::scale(Vector3((float)renderSystem->size().y() / renderSystem->size().x(), 1, 1));
	//} else {
	//	// not so wide-screen!
	//	float factorX = ratio > 1 ? 1 / ratio : 1;
	//	float factorY = ratio < 1 ? 1 / ratio : 1;
	//	distort = Matrix4x4::scale(Vector3(1, (float)renderSystem->size().x() / renderSystem->size().y(), 1));
	//}
	// 1840 x 900

	//Matrix4x4 distort = Matrix4x4::scale(Vector3(1, 1, 1.0f)); // Stretched

	return scaleDown * distort;
}

Matrix4x4 Camera::getClipToCameraMatrix() {
	return this->getCameraToClipMatrix().invert();
}

Vector3 Camera::worldToCamera(Vector3 world) {
	return (this->getWorldToCameraMatrix() * world.toVector4(1)).xyz();
}

Vector3 Camera::cameraToWorld(Vector3 camera) {
	return (this->getCameraToWorldMatrix() * camera.toVector4(1)).xyz();
}

Vector2 Camera::cameraToClip(Vector3 camera) {
	return (this->getCameraToClipMatrix() * camera.toVector4(1)).xy();
}

Vector2 Camera::worldToClip(Vector3 world) {
	return this->cameraToClip(this->worldToCamera(world));
}