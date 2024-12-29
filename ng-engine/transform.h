#pragma once

#include "vector3.h"
#include "matrix4x4.h"
#include "component.h"
#include "quaternion.h"

/**
* The transform is the only component needed on EVERY game object. It specifies how objects are located in the scene.
*/
class Transform : public Component {
public:
	/**
	* The local position of the transform
	*/
	Vector3 position = Vector3(0, 0, 0);

	/**
	* The local rotation of the transform
	*/
	Quaternion rotation = Quaternion::identity();

	/**
	* The local scale of the transform
	*/
	Vector3 scale = Vector3(1, 1, 1);

	/**
	* The parent transform of this transform. 
	* This essentially allows transforms to build a linked list data structure.
	*/
	Transform* parent = nullptr;

	/**
	* Returns the transformation matrix to transform coordinates from local space to world space
	* This already respects the transform hierarchy.
	*/
	Matrix4x4 getLocalToWorldMatrix();

	/**
	* Returns the transformation matrix to transform coordinates from world space to local space
	* This already respects the transform hierarchy.
	*/
	Matrix4x4 getWorldToLocalMatrix();

	/**
	* Transforms the given coordinates from local space to world space
	*/
	Vector4 localToWorld(Vector4 local);
	Vector3 localToWorld(Vector3 local);
	Vector2 localToWorld(Vector2 local);

	/**
	* Transforms the given value from local space to world space by only applying the scale (no rotation or translation)
	*/
	float localToWorld(float local);

	/**
	* Transforms the given coordinates from world space to local space.
	*/
	Vector4 worldToLocal(Vector4 world);

	/**
	* Transforms the given coordinates from world space to local space.
	*/
	Vector3 worldToLocal(Vector3 world);

	/**
	* Transforms the given coordinates from world space to local space.
	*/
	Vector2 worldToLocal(Vector2 world);

	/**
	* Transforms the given value from world space to local space by only applying the scale (no rotation or translation)
	*/
	float worldToLocal(float world);

	/**
	* Moves the transform by the specified amount
	*/
	void move(Vector3 vector);

	/**
	* Moves the transform by the specified amount into the x and y direction
	*/
	void move(Vector2 vector);

	/**
	* Returns a list of references to all transforms in the scene which have this transform as their parent.
	*/
	std::vector<Transform*> getChildren();

	/**
	* Returns the global position of this transform
	*/
	Vector3 getGlobalPosition();

	/**
	* Returns the global rotation of this transform
	*/
	Quaternion getGlobalRotation();

	/**
	* Returns the global scale of this transform
	*/
	Vector3 getGlobalScale();
};