#pragma once


// forward declare GameObject to avoid circular references (GameObject is importing Component)
class GameObject; 

// forward declare Transform to avoid circular references (Transform is importing Component)
class Transform;

// forward declare Scene to avoid circular references (Scene is importing GameObject, which imports Component)
class Scene;

class Component {
public:
	GameObject* gameObject; // this should only be written to by the GameObject
	Component();

	Scene* scene() const; // Quick access for this->gameObject->scene
	Transform* transform() const; // Quick access for this->gameObject->transform()

	virtual void update();
};