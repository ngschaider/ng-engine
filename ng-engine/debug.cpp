#include "debug.h"
#include <imgui.h>
#include <stdio.h>
#include "camera.h"
#include "scene.h"
#include "render_system.h"

void Debug::line(Vector3 start, Vector3 end, Color color) {
	this->lines.push_back({
		start,
		end,
		color,
		});
}

void Debug::earlyUpdate() {
	this->lines.clear();
}
void Debug::render() {
	ImDrawList* drawList = ImGui::GetForegroundDrawList();

	Camera* camera = this->scene()->getComponent<Camera>();
	if (camera == nullptr) return;

	RenderSystem* renderSystem = this->scene()->getComponent<RenderSystem>();
	if (renderSystem == nullptr) return;

	Matrix4x4 worldToCamera = camera->getWorldToCameraMatrix();
	Matrix4x4 cameraToClip = camera->getCameraToClipMatrix();
	Matrix4x4 clipToScreen = renderSystem->getClipToScreenMatrix();
	Matrix4x4 worldToScreen = clipToScreen * cameraToClip * worldToCamera;
    for (const Line& line : this->lines) {
		Vector2 start = (worldToScreen * line.start.toVector4(1)).xy();
		Vector2 end = (worldToScreen * line.end.toVector4(1)).xy();
		ImU32 color = IM_COL32(line.color.r(), line.color.g(), line.color.b(), 255);
		drawList->AddLine(ImVec2(start.x(), start.y()), ImVec2(end.x(), end.y()), color, 1);
	}

	char str[120];
	sprintf_s(str, "%f / %f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
	drawList->AddText(ImGui::GetMousePos(), IM_COL32_BLACK, str);
}

//void Debug::circle(Vector3 center, float radius) {
// 
//}

//void Debug::rect(Vector3 position, float width, float height) {
//
//}