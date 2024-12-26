#pragma once

#include "component.h"
#include "matrix4x4.h"

class Camera : public Component {
public:
	Vector2 size = Vector2(20, 20);
	bool isActive = true;
	Camera();

	/**
	* Returns the aspect ratio of the camera's view
	*/
	float ratio();

	/**
	* Returns the transformation matrix that transforms coordinates from world space to camera space
	*/
	Matrix4x4 getWorldToCameraMatrix();

	/**
	* Returns the transformation matrix that transforms coordinates from camera space to world space
	*/
	Matrix4x4 getCameraToWorldMatrix();

	/**
	* Returns the transformation matrix that transforms coordinates from camera space to clip space
	*/
	Matrix4x4 getCameraToClipMatrix();

	/**
	* Returns the transformation matrix that transforms coordinates from clip space to camera space
	*/
	Matrix4x4 getClipToCameraMatrix();

	/**
	* Transforms the given coordinates from world space to camera space
	*/
	Vector3 worldToCamera(Vector3 world);

	/**
	* Transforms the given coordinates from camera space to world space
	*/
	Vector3 cameraToWorld(Vector3 camera);

	/**
	* Transforms the given coordinates from camera space to clip space
	* This is a lossy operation as the camera applies an orthographic projection
	*/
	Vector2 cameraToClip(Vector3 camera);

	/**
	* Transforms the given coordinates from world space to clip space
	* This is a lossy operation as the camera applies an orthographic projection
	*/
	Vector2 worldToClip(Vector3 camera);
};