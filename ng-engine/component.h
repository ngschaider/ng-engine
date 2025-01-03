#pragma once

// forward declare GameObject to avoid circular references (GameObject is importing Component)
class GameObject; 

// forward declare Transform to avoid circular references (Transform is importing Component)
class Transform;

// forward declare Scene to avoid circular references (Scene is importing GameObject, which imports Component)
class Scene;

// forward declare Engine to avoid circular references (Engine is importing Scene, which imports GameObject, which imports Component)
class Engine;


/**
* Base class for components. This should not be instantiated directly as it really does nothing.
* In most cases you want to create a new class, inherit from this one and overwrite the update() method.
* Often, you also want to listen to some of the events.
*/
class Component {
public:
	/**
	* Wether this component for itself is enabled
	*/
	bool isEnabledSelf = true;

	/**
	* Returns wether this component should be updated.
	* This value is composed by the "isEnabledSelf" property of both this instance and it's parents.
	*/
	bool getEnabled();

	/**
	* Setter for "isEnabledSelf".
	*/
	void setEnabled(bool enabled);

	/**
	* The game object this component is attached to, this should only be written to by the game object
	*/
	GameObject* gameObject = nullptr;

	/**
	* Quick access for this->gameObject->scene including null-checks
	*/
	Scene* scene() const; 

	/**
	* Quick access for this->gameObject->scene->engine including null-checks
	*/
	Engine* engine() const; 

	/**
	* Quick access for this->gameObject->transform() including null-checks
	*/
	Transform* transform() const; 

	/**
	* The early update signal of the engine.
	* This gets relayed here by the game object.
	*/
	virtual void earlyUpdate();

	/**
	* The update signal of the engine.
	* This gets relayed here by the game object.
	*/
	virtual void update();

	/**
	* The late update signal of the engine.
	* This gets relayed here by the game object.
	*/
	virtual void lateUpdate();

	/**
	* The fixed update signal of the engine.
	* This gets relayed here by the game object
	*/
	virtual void fixedUpdate();

	/**
	* called when the component gets attached to a game object, this should only be called by the game object
	*/
	virtual void addedToGameObject();

	/**
	* called when the component gets removed from a game object, this should only be called by the game object
	*/
	virtual void removedFromGameObject(); 

	/**
	* called when this->scene() changes from NULL to a scene instance, this should only be called by the game object
	*/
	virtual void addedToScene(); 

	/**
	* called when this->scene() changes from a scene instance to NULL, this should only be called by the game object
	*/
	virtual void removedFromScene();

	/**
	* called when this->engine() changes from NULL to an engine instance, this should only be called by the game object
	*/
	virtual void addedToEngine(); 

	/**
	* called when this->engine() changes from engine instance to NULL, this should only be called by the game object
	*/
	virtual void removedFromEngine(); 

	/**
	* called when this->engine() gets started, this should only be called by the game object
	*/
	virtual void started();

	/**
	* called when this->engine() gets stopped, this should only be called by the game object
	*/
	virtual void stopped();

};