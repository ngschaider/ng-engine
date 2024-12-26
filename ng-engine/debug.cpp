#include "debug.h"
#include <imgui.h>
#include <stdio.h>
#include "camera.h"
#include "scene.h"
#include "render_system.h"

void Debug::earlyUpdate() {
	this->lines.clear();
	this->rectangles.clear();
	this->circles.clear();
}

void Debug::render() {
	ImDrawList* drawList = ImGui::GetForegroundDrawList();

	Camera* camera = this->scene()->getComponent<Camera>();
	if (camera == nullptr) return;

	RenderSystem* renderSystem = this->scene()->getComponent<RenderSystem>();
	if (renderSystem == nullptr) return;

    for (const Line& line : this->lines) {
		// ImGui's coordinate system is top-left based, while ours is bottom-left based. We need to flip the y-axis!
		Vector3 startFlipped = Vector3(line.start.x(), -line.start.y(), line.start.z());
		Vector3 endFlipped = Vector3(line.end.x(), -line.end.y(), line.end.z());

		Vector2 start = renderSystem->clipToScreen(camera->worldToClip(startFlipped));
		Vector2 end = renderSystem->clipToScreen(camera->worldToClip(endFlipped));
		
		drawList->AddLine(ImVec2(start.x(), start.y()), ImVec2(end.x(), end.y()), IM_COL32_BLACK, 1);
	}
	for (const Circle& circle : this->circles) {
		Vector3 flipped = Vector3(circle.position.x(), -circle.position.y(), circle.position.z());
		
		Vector3 cam = camera->worldToCamera(flipped);
		Vector2 clip = camera->cameraToClip(cam);
		Vector2 center = renderSystem->clipToScreen(clip);

		// ImGui's coordinate system is top-left based, while ours is bottom-left based. We need to flip the y-axis!
		drawList->AddCircle(ImVec2(center.x(), center.y()), circle.radius, IM_COL32_BLACK);
	}
	for (Rect rect : this->rectangles) {
		// ImGui's coordinate system is top-left based, while ours is bottom-left based. We need to flip the y-axis.
		// We do this by using topLeft/bottomRight bottomLeft/topRight.
		Vector2 min = renderSystem->clipToScreen(camera->worldToClip(rect.topLeft().toVector3(0)));
		Vector2 max = renderSystem->clipToScreen(camera->worldToClip(rect.bottomRight().toVector3(0)));

		drawList->AddRect(ImVec2(min.x(), min.y()), ImVec2(max.x(), max.y()), IM_COL32_BLACK);
	}

	char str[120];
	sprintf_s(str, "%f / %f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
	drawList->AddText(ImGui::GetMousePos(), IM_COL32_BLACK, str);
}

void Debug::circle(Vector3 center, float radius) {
	this->circles.push_back({
		center,
		radius,
		});
}

void Debug::rect(Rect rect) {
	this->rectangles.push_back(rect);
}

void Debug::line(Vector3 start, Vector3 end) {
	this->lines.push_back({
		start,
		end,
		});
}