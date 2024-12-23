#include "inspector_window.h"
#include "imgui.h"
#include "hierarchy_window.h"
#include "triangle_renderer.h"
#include "rigid_body.h"
#include "control_velocity.h"
#include "input_system.h"
#include "camera.h"
#include <typeinfo>
#include "menu_bar.h"
#include "rectangle_collider_2d.h"
#include "circle_collider_2d.h"
#include "rectangle_renderer.h"
#include "render_system.h"
#include "text_renderer.h"
#include "collision_system.h"
#include "imgui_renderer.h"
#include "polygon_collider_2d.h"
#include "circle_collider_2d.h"
#include "misc/cpp/imgui_stdlib.h"
#include <map>

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

		if (this->inspectedGameObject->components.empty()) {
			ImGui::Text("The selected game object does not have any components attached.");
		}
		else {
			for (Component* component : this->inspectedGameObject->components) {
				ImGui::PushID(component);

				std::string name = std::string(typeid(*component).name());
				if (ImGui::CollapsingHeader(name.substr(6).c_str())) {
					Transform* transform = dynamic_cast<Transform*>(component);
					RigidBody* rigidBody = dynamic_cast<RigidBody*>(component);
					RectangleCollider2D* rectangleCollider = dynamic_cast<RectangleCollider2D*>(component);
					CircleCollider2D* circleCollider = dynamic_cast<CircleCollider2D*>(component);
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
						if (ImGui::DragFloat3("##linAcc", linAcc)) {
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
					else if (rectangleCollider != nullptr) {
						ImGui::LabelText("##pos_lbl", "Position");
						ImGui::SameLine(100);
						float posValues[2] = { rectangleCollider->rect.position().x(), rectangleCollider->rect.position().y() };
						if (ImGui::DragFloat2("##position", posValues)) {
							rectangleCollider->rect = Rect(Vector2(posValues[0], posValues[1]), rectangleCollider->rect.size(), rectangleCollider->rect.anchorPoint());
						}

						ImGui::LabelText("##size_lbl", "Size");
						ImGui::SameLine(100);
						float sizeValues[2] = { rectangleCollider->rect.size().x(), rectangleCollider->rect.size().y() };
						if (ImGui::DragFloat2("##size", sizeValues)) {
							rectangleCollider->rect = Rect(rectangleCollider->rect.position(), Vector2(sizeValues[0], sizeValues[1]), rectangleCollider->rect.anchorPoint());
						}

						ImGui::LabelText("##anchorPoint_lbl", "Anchor Point");
						ImGui::SameLine(100);
						std::map<AnchorPoint, std::string> m = {
							{AnchorPoint::BottomCenter, "BottomCenter"},
							{AnchorPoint::BottomLeft, "BottomLeft"},
							{AnchorPoint::BottomRight, "BottomRight"},
							{AnchorPoint::CenterCenter, "CenterCenter"},
							{AnchorPoint::LeftCenter, "LeftCenter"},
							{AnchorPoint::RightCenter, "RightCenter"},
							{AnchorPoint::TopCenter, "TopCenter"},
							{AnchorPoint::TopLeft, "TopLeft"},
							{AnchorPoint::TopRight, "TopRight"},
						};
						if (ImGui::BeginCombo("##anchorPoint", m[rectangleCollider->rect.anchorPoint()].c_str())) {
							for (std::pair<AnchorPoint, std::string> pair : m) {
								if (ImGui::Selectable(pair.second.c_str())) {
									rectangleCollider->rect = Rect(rectangleCollider->rect.position(), rectangleCollider->rect.size(), pair.first);
								}
							}
							ImGui::EndCombo();
						}
					}
					else {
						ImGui::Text("This component is not supported by the inspector.");
					}
				}

				if (ImGui::BeginPopupContextItem("component popup")) {
					if (ImGui::MenuItem("Remove")) {
						this->inspectedGameObject->deleteComponentLater(component);
					}
					ImGui::EndPopup();
				}

				ImGui::PopID();
			}
		}

		if (ImGui::BeginPopupContextItem("add component popup")) {
			if (ImGui::BeginMenu("Rendering")) {
				if (ImGui::MenuItem("SquareRenderer")) {
					this->inspectedGameObject->addComponent(new RectangleRenderer());
				}
				if (ImGui::MenuItem("TriangleRenderer")) {
					this->inspectedGameObject->addComponent(new TriangleRenderer());
				}
				if (ImGui::MenuItem("ImGuiRenderer")) {
					this->inspectedGameObject->addComponent(new ImGuiRenderer());
				}
				if (ImGui::MenuItem("RenderSystem")) {
					this->inspectedGameObject->addComponent(new RenderSystem());
				}
				if (ImGui::MenuItem("TextRenderer")) {
					this->inspectedGameObject->addComponent(new TextRenderer());
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Collision")) {
				if (ImGui::MenuItem("RectangleCollider2D")) {
					this->inspectedGameObject->addComponent(new RectangleCollider2D());
				}
				if (ImGui::MenuItem("CircleCollider2D")) {
					this->inspectedGameObject->addComponent(new CircleCollider2D());
				}
				if (ImGui::MenuItem("CollisionSystem")) {
					this->inspectedGameObject->addComponent(new CollisionSystem());
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Core")) {
				if (ImGui::MenuItem("MenuBar")) {
					this->inspectedGameObject->addComponent(new MenuBar());
				}
				if (ImGui::MenuItem("Camera")) {
					this->inspectedGameObject->addComponent(new Camera());
				}
				if (ImGui::MenuItem("RigidBody")) {
					this->inspectedGameObject->addComponent(new RigidBody());
				}
				if (ImGui::MenuItem("InputSystem")) {
					this->inspectedGameObject->addComponent(new InputSystem());
				}
				if (ImGui::MenuItem("HierarchyWindow")) {
					this->inspectedGameObject->addComponent(new HierarchyWindow());
				}
				if (ImGui::MenuItem("InspectorWindow")) {
					this->inspectedGameObject->addComponent(new InspectorWindow());
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Scripts")) {
				if (ImGui::MenuItem("ControlVelocity")) {
					this->inspectedGameObject->addComponent(new ControlVelocity());
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		if (ImGui::Button("Add Component")) {
			ImGui::OpenPopup("add component popup");
		}
	}

	ImGui::End();
}