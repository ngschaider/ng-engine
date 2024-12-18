#include "hierarchy_window.h"
#include "imgui.h"
#include "scene.h"

HierarchyWindow::HierarchyWindow() {

}

void HierarchyWindow::render() {
	ImGui::Begin("Hierarchy");
	if (ImGui::BeginListBox("##hierarchy_list")) {
		for (GameObject* gameObject : this->scene()->gameObjects) {
			ImGui::Selectable(gameObject->name.c_str());
		}
		ImGui::EndListBox();
	}
	ImGui::End();
}