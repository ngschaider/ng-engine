#pragma once

#include <math.h>

// forward declare Vector3 to avoid circular references (Vector3 is importing Vector2)
class Vector3;

// forward declare Vector4 to avoid circular references (Vector4 is importing Vector2)
class Vector4;

/**
* Represents a 2-dimensional vector
*/
class Vector2 {
private:
	float _x;
	float _y;
public:
	/**
	* Returns the x-component of the vector [x y]
	*/
	float x() const;

	/**
	* Returns the y-component of the vector [x y]
	*/
	float y() const;

	/**
	* Constructs a new vector using the given values
	*/
	Vector2(float x, float y);
	
	/**
	* Adds a vector to this vector and returns the result as a new vector
	*/
	Vector2 operator+(Vector2 v);

	/**
	* Subtracts a vector from this vector and returns the result as a new vector
	*/
	Vector2 operator-(Vector2 v);

	/**
	* Multiplies the vector with a given scalar (element-wise) and returns the result as a new vector
	*/
	Vector2 operator*(float v);

	/**
	* Divides the vector by a given scalar (element-wise) and returns the result as a new vector
	*/
	Vector2 operator/(float v);

	/**
	* Returns a Vector3 composed of the x and y components of this vector and the provided z component.
	*/
	Vector3 toVector3(float z);

	/**
	* Returns a Vector4 composed of the x and y components of this vector and the provided z and w components.
	*/
	Vector4 toVector4(float z, float w);

	/**
	* Returns the squared magnitude (squared "length") of this vector.
	* If performance is an issue use this instead of Vector2::magnitude() if possible.
	*/
	float magnitudeSquared();

	/**
	* Returns the magnitude ("length") of this vector.
	* If performance is an issue use Vector2::magnitudeSquared() instead of this if possible.
	*/
	float magnitude();

	/**
	* Returns the angle of this vector measured from the x-axis to the vector.
	*/
	float angle();

	/**
	* Returns the squared distance from this vector to another vector.
	* If performance is an issue use this instead of Vector2::distance(...) if possible.
	*/
	float distanceSquared(Vector2 v);

	/**
	* Returns the distance between this vector and another vector.
	* If performance is an issue use Vector2::distanceSquared(...) instead of this if possible.
	*/
	float distance(Vector2 v);

	/**
	* Returns the dot product between this vector and another vector.
	*/
	float dot(Vector2 v);
};