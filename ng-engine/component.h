#pragma once

// forward declare GameObject to avoid circular references (GameObject is importing Component)
class GameObject; 

// forward declare Transform to avoid circular references (Transform is importing Component)
class Transform;

// forward declare Scene to avoid circular references (Scene is importing GameObject, which imports Component)
class Scene;

// forward declare Engine to avoid circular references (Engine is importing Scene, which imports GameObject, which imports Component)
class Engine;

class Component {
public:
	GameObject* gameObject; // the game object this component is attached to, this should only be written to by the game object
	Component();
	virtual ~Component();

	Scene* scene() const; // Quick access for this->gameObject->scene including null-checks
	Engine* engine() const; // Quick access for this->gameObject->scene->engine including null-checks
	Transform* transform() const; // Quick access for this->gameObject->transform() including null-checks

	virtual void update();

	// events
	virtual void addedToGameObject(); // called when the component gets attached to a game object, this should only be called by the game object
	virtual void removedFromGameObject(); // called when the component gets removed from a game object, this should only be called by the game object
	virtual void addedToScene(); // called when this->scene() changes from NULL to a scene instance, this should only be called by the game object
	virtual void removedFromScene(); // called when this->scene() changes from a scene instance to NULL, this should only be called by the game object
	virtual void addedToEngine(); // called when this->engine() changes from NULL to an engine instance, this should only be called by the game object
	virtual void removedFromEngine(); // called when this->engine() changes from engine instance to NULL, this should only be called by the game object
	virtual void started(); // called when this->engine() gets started, this should only be called by the game object
	virtual void stopped(); // called when this->engine() gets stopped, this should only be called by the game object

};