#include "renderer.h"
#include "camera.h"
#include "transform.h"
#include "scene.h"
#include <exception>

void Renderer::render(Graphics* graphics) {
	graphics->fillColor = this->fillColor;
	graphics->doFill = this->doFill;

	graphics->strokeColor = strokeColor;
	graphics->doStroke = this->doStroke;

	graphics->lineWidth = this->lineWidth;
	graphics->fontSize = this->fontSize;

	Camera* camera = this->scene()->getActiveCamera();
	if (camera == nullptr) throw new std::exception("Renderer requries an active camera in the scene.");

	Matrix4x4 localToWorld = this->transform()->getLocalToWorldMatrix();
	Matrix4x4 worldToCamera = camera->getWorldToCameraMatrix();
	Matrix4x4 cameraToClip = camera->getCameraToClipMatrix();

	if (this->space == RendererSpace::Local) {
		// local -> world -> camera -> clip
		Matrix4x4 m = cameraToClip * worldToCamera * localToWorld;
		graphics->setTransformationMatrix(m);
	}
	else if (this->space == RendererSpace::World) {
		// world -> camera -> clip
		graphics->setTransformationMatrix(cameraToClip * worldToCamera);
	}
	else if (this->space == RendererSpace::Camera) {
		// camera -> clip
		graphics->setTransformationMatrix(cameraToClip);
	}
	else if (this->space == RendererSpace::Clip) {
		graphics->setTransformationMatrix(Matrix4x4::identity());
	}
	else if (this->space == RendererSpace::Screen) {
		Matrix4x4 screenToClip = graphics->getScreenToClipMatrix();
		graphics->setTransformationMatrix(screenToClip);
	}

}