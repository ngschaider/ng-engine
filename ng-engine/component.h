#pragma once


// forward declare GameObject to avoid circular references (GameObject is importing Component)
class GameObject; 

// forward declare Transform to avoid circular references (Transform is importing Component)
class Transform;

class Component {
public:
	GameObject* gameObject; // this should only be written to by the GameObject
	Component();
	Transform* transform() const;

	virtual void update();
};