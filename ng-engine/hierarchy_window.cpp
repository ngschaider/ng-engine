#include "hierarchy_window.h"
#include "imgui.h"
#include "scene.h"
#include "inspector_window.h"

HierarchyWindow::HierarchyWindow() {

}

void HierarchyWindow::render() {
	static GameObject* selectedGameObject = nullptr;

	ImGui::Begin("Hierarchy");

	if (ImGui::BeginListBox("##hierarchy_list", ImVec2(-1, -1))) {
		for (GameObject* gameObject : this->scene()->gameObjects) {
			ImGui::PushID(gameObject);
			if (ImGui::Selectable(gameObject->name.c_str(), gameObject == selectedGameObject)) {
				InspectorWindow* inspectorWindow = this->scene()->getComponent<InspectorWindow>();
				if (inspectorWindow != nullptr) {
					inspectorWindow->setInspectedGameObject(gameObject);
				}
				selectedGameObject = gameObject;
			}
			ImGui::PopID();
		}
		ImGui::EndListBox();
	}

	ImGui::End();
}