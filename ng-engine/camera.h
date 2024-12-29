#pragma once

#include "component.h"
#include "matrix4x4.h"
#include "vector3.h"
#include "vector2.h"

/**
* The camera is part of the rendering system and specifies properties regarding the point-of-view.
* It features an orthographic projection, and establishes what we call "camera space". Camera space is located between world space and clip space.
* Therefore the camera also provides transformation matrices for world<->camera and camera<->clip.
*/
class Camera : public Component {
public:
	/**
	* The size (width/height) of the camera's view frustum
	*/
	Vector2 size = Vector2(20, 20);

	/**
	* Wether this camera is active.
	* Only the first active camera in the scene gets rendered.
	*/
	bool isActive = true;

	/**
	* Returns the aspect ratio of the camera's view
	*/
	float ratio() const;

	/**
	* Returns the transformation matrix that transforms coordinates from world space to camera space
	*/
	Matrix4x4 getWorldToCameraMatrix() const;

	/**
	* Returns the transformation matrix that transforms coordinates from camera space to world space
	*/
	Matrix4x4 getCameraToWorldMatrix() const;

	/**
	* Returns the transformation matrix that transforms coordinates from camera space to clip space
	*/
	Matrix4x4 getCameraToClipMatrix() const;

	/**
	* Returns the transformation matrix that transforms coordinates from clip space to camera space
	*/
	Matrix4x4 getClipToCameraMatrix() const;

	/**
	* Transforms the given coordinates from world space to camera space
	*/
	Vector3 worldToCamera(Vector3 world) const;

	/**
	* Transforms the given coordinates from camera space to world space
	*/
	Vector3 cameraToWorld(Vector3 camera) const;

	/**
	* Transforms the given coordinates from camera space to clip space
	* This is a lossy operation as the camera applies an orthographic projection
	*/
	Vector2 cameraToClip(Vector3 camera) const;

	/**
	* Transforms the given coordinates from world space to clip space
	* This is a lossy operation as the camera applies an orthographic projection
	*/
	Vector2 worldToClip(Vector3 camera) const;
};