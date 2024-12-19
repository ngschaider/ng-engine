#pragma once

#include "math.h"
#include "vector3.h"

class Quaternion {
private:
	float _x;
	float _y;
	float _z;
	float _w;
public:
	/**
	* Returns the identity quaternion
	*/
	static Quaternion identity();

	/**
	* Returns a quaternion that represents a rotation around the provided axis by the provided angle (in degrees)
	*/
	static Quaternion fromAngleAxis(float deg, Vector3 axis);

	/**
	* Returns a new quaternion from the provided euler angles (in degrees)
	* TODO: Find out the correct order of the function signature and change the naming to x, y and z
	*/
	static Quaternion fromEulerAngles(float pitch, float roll, float yaw);

	/**
	* Returns a new quaternion from the provided euler angles (in degree)
	*/
	static Quaternion fromEulerAngles(Vector3 deg);

	/**
	* Interpolates linearly between two provided quaternions by the interpolant t (0 <= t <= 1)
	* The result of the interpolation is returned as a new quaternion
	*/
	static Quaternion Lerp(Quaternion a, Quaternion b, float t);

	/**
	* Creates a new quaternion from the provided values
	* These values do NOT represent rotations in degrees or something similar. 
	* Only use this constructor if you really know quaternions and how they represent rotations.
	*/
	Quaternion(float x, float y, float z, float w);

	/**
	* Returns the x component of the quaternion [x y z w]
	*/
	float x() const;

	/**
	* Returns the y component of the quaternion [x y z w]
	*/
	float y() const;

	/**
	* Returns the z component of the quaternion [x y z w]
	*/
	float z() const;

	/**
	* Returns the w component of the quaternion [x y z w]
	*/
	float w() const;

	/**
	* Returns a vector representing the rotation of the quaternion in degrees
	*/
	Vector3 eulerAngles() const;

	/**
	* Returns a Vector3 consisting of the vector components of the quaternion (x, y and z)
	*/
	Vector3 vector() const;

	/**
	* Multiplies the quaternion with another quaternion and returns the result as a new quaternion.
	* This effectively combines the rotations each quaternion would produce
	*/
	Quaternion operator*(Quaternion q);
};