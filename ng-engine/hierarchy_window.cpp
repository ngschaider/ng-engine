#include "hierarchy_window.h"
#include "imgui.h"
#include "scene.h"
#include "inspector_window.h"
#include <vector>

void HierarchyWindow::renderGameObject(GameObject* gameObject) {
	static GameObject* selectedGameObject = nullptr;

	std::vector<Transform*> children = gameObject->transform()->getChildren();

	if (children.empty()) {
		ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());

		// There are no children, this is the last node in the tree
		if (ImGui::Selectable(gameObject->name.c_str(), gameObject == selectedGameObject)) {
			InspectorWindow* inspectorWindow = this->scene()->getComponent<InspectorWindow>();
			if (inspectorWindow != nullptr) {
				inspectorWindow->inspectedGameObject = gameObject;
			}
			selectedGameObject = gameObject;
		}

		ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
	}
	else {
		// We have children, create a tree node here!
		ImGuiTreeNodeFlags flags = selectedGameObject == gameObject ? ImGuiTreeNodeFlags_Selected : 0;
		flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
		flags |= ImGuiTreeNodeFlags_OpenOnArrow;
		bool nodeOpen = ImGui::TreeNodeEx(gameObject->name.c_str(), flags);

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
			InspectorWindow* inspectorWindow = this->scene()->getComponent<InspectorWindow>();
			if (inspectorWindow != nullptr) {
				inspectorWindow->inspectedGameObject = gameObject;
			}
			selectedGameObject = gameObject;
		}

		if (nodeOpen) {
			int i = 0;
			for (Transform* child : children) {
				i++;

				ImGui::PushID(i);
				this->renderGameObject(child->gameObject);
				ImGui::PopID();
			}

			ImGui::TreePop();
		}
	}
}

void HierarchyWindow::render() {
	ImGui::Begin("Hierarchy");

	if (ImGui::BeginListBox("##hierarchy_list", ImVec2(-1, -1))) {
		for (GameObject* gameObject : this->scene()->gameObjects) {
			if (gameObject->transform()->parent != nullptr) continue;
			ImGui::PushID(gameObject);
			this->renderGameObject(gameObject);
			ImGui::PopID();
		}
		ImGui::EndListBox();
	}

	ImGui::End();
}