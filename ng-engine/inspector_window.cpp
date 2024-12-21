#include "inspector_window.h"
#include "imgui.h"
#include "hierarchy_window.h"
#include "rigid_body.h"
#include <typeinfo>
#include "misc/cpp/imgui_stdlib.h"

InspectorWindow::InspectorWindow() {
	this->inspectedGameObject = nullptr;
}

void InspectorWindow::setInspectedGameObject(GameObject* gameObject) {
	this->inspectedGameObject = gameObject;
}

void InspectorWindow::render() {
	ImGui::Begin("Inspector");

	if (this->inspectedGameObject == nullptr) {
		ImGui::Text("No game object selected.");
		ImGui::Text("Select a game object in the Hierarchy to show details here.");
	}
	else {
		ImGui::InputText("##name", &this->inspectedGameObject->name);

		for (Component* component : this->inspectedGameObject->components) {
			ImGui::PushID(component);

			std::string name = std::string(typeid(*component).name());
			if (ImGui::CollapsingHeader(name.substr(6).c_str())) {
				Transform* transform = dynamic_cast<Transform*>(component);
				RigidBody* rigidBody = dynamic_cast<RigidBody*>(component);
				if (transform != nullptr) {
					ImGui::LabelText("##position_lbl", "Position");
					float posValues[3] = { transform->position.x(), transform->position.y(),  transform->position.z() };
					ImGui::SameLine(100);
					if (ImGui::DragFloat3("##position", posValues)) {
						transform->position = Vector3(posValues[0], posValues[1], posValues[2]);
					}

					ImGui::LabelText("##rotation_lbl", "Rotation");
					float rotValues[3] = { transform->rotation.eulerAngles().x(), transform->rotation.eulerAngles().y(), transform->rotation.eulerAngles().z() };
					ImGui::SameLine(100);
					if (ImGui::DragFloat3("##rotation", rotValues)) {
						transform->rotation = Quaternion::fromEulerAngles(rotValues[0], rotValues[1], rotValues[2]);
					}

					ImGui::LabelText("##scale_lbl", "Scale");
					float scaleValues[3] = { transform->scale.x(), transform->scale.y(), transform->scale.z() };
					ImGui::SameLine(100);
					if (ImGui::DragFloat3("##scale", scaleValues)) {
						transform->scale = Vector3(scaleValues[0], scaleValues[1], scaleValues[2]);
					}
				}
				else if (rigidBody != nullptr) {
					ImGui::LabelText("##mass_lbl", "Mass");
					ImGui::SameLine(180);
					ImGui::DragFloat("##mass", &rigidBody->mass);

					ImGui::LabelText("##restitution_lbl", "Restitution");
					ImGui::SameLine(180);
					ImGui::DragFloat("##restitution", &rigidBody->restitution);

					ImGui::LabelText("##linVel_lbl", "Linear Velocity");
					float linVel[3] = { rigidBody->linearVelocity.x(), rigidBody->linearVelocity.y(), rigidBody->linearVelocity.z() };
					ImGui::SameLine(180);
					if (ImGui::DragFloat3("##linVel", linVel)) {
						rigidBody->linearVelocity = Vector3(linVel[0], linVel[1], linVel[2]);
					}

					ImGui::LabelText("##angvel_lbl", "Angular Velocity");
					float angVel[3] = { rigidBody->angularVelocity.x(), rigidBody->angularVelocity.y(), rigidBody->angularVelocity.z() };
					ImGui::SameLine(180);
					if (ImGui::DragFloat3("##angVel", angVel)) {
						rigidBody->angularVelocity = Quaternion::fromEulerAngles(angVel[0], angVel[1], angVel[2]);
					}

					ImGui::LabelText("##linacc_lbl", "Linear Acceleration");
					float linAcc[3] = { rigidBody->linearAcceleration.x(), rigidBody->linearAcceleration.y(), rigidBody->linearAcceleration.z() };
					ImGui::SameLine(180);
					if (ImGui::DragFloat3("##linAcc", angVel)) {
						rigidBody->linearAcceleration = Vector3(linAcc[0], linAcc[1], linAcc[2]);
					}

					ImGui::LabelText("##angacc_lbl", "Angular Acceleration");
					float angAcc[3] = { 
						rigidBody->angularAcceleration.eulerAngles().x(), rigidBody->angularAcceleration.eulerAngles().y(), rigidBody->angularAcceleration.eulerAngles().z()
					};
					ImGui::SameLine(180);
					if (ImGui::DragFloat3("##angAcc", angAcc)) {
						rigidBody->angularVelocity = Quaternion::fromEulerAngles(angAcc[0], angAcc[1], angAcc[2]);
					}
				}
				else {
					ImGui::Text("This component is not supported by the inspector.");
				}
			}

			ImGui::PopID();
		}
	}

	ImGui::End();
}