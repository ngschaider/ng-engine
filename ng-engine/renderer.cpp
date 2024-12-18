#include "renderer.h"
#include "camera.h"
#include "transform.h"
#include "scene.h"
#include "matrix4x4.h"
#include <exception>
#include "render_system.h"

Matrix4x4 Renderer::getTransformationMatrix() {
	Camera* camera = this->scene()->getActiveCamera();
	if (camera == nullptr) throw new std::exception("Renderer requries an active camera in the scene.");

	Matrix4x4 localToWorld = this->transform()->getLocalToWorldMatrix();
	Matrix4x4 worldToCamera = camera->getWorldToCameraMatrix();
	Matrix4x4 cameraToClip = camera->getCameraToClipMatrix();

	//Matrix4x4 m = Matrix4x4(
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//	0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//);
	//graphics->setTransformationMatrix(m);

	//graphics->setTransformationMatrix(localToWorld);

	if (this->space == RendererSpace::Local) {
		// local -> world -> camera -> clip
		return cameraToClip * worldToCamera * localToWorld;
	}
	else if (this->space == RendererSpace::World) {
		// world -> camera -> clip
		return cameraToClip * worldToCamera;
	}
	else if (this->space == RendererSpace::Camera) {
		// camera -> clip
		return cameraToClip;
	}
	else if (this->space == RendererSpace::Clip) {
		return Matrix4x4::identity();
	}
	else if (this->space == RendererSpace::Screen) {
		RenderSystem* renderSystem = this->scene()->getComponent<RenderSystem>();
		if (renderSystem == nullptr) throw new std::exception("Renderer requires a RenderSystem component to be present in the current scene.");
		return renderSystem->getScreenToClipMatrix();
	}

	throw new std::exception("Encountered unexpected RendererSpace");
}

void Renderer::beforeRender() {
}
void Renderer::render() {
}
void Renderer::afterRender() {
}