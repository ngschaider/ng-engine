#pragma once

#include "vector2.h"
#include <array>
#include <vector>
#include <exception>

/**
* Represents a 3x3 matrix
*/
class Matrix3x3 {
private:
	std::array<float, 9> values;
public:
	/**
	* returns a 3x3 identity matrix
	*/
	static Matrix3x3 identity();

	/**
	* returns a transformation matrix for translating by the given vector
	*/
	static Matrix3x3 translate(Vector2);

	/**
	* returns a transformation matrix for rotating by the given angle
	*/
	static Matrix3x3 rotate(float);

	/**
	* returns a transformation matrix for scaling by the given vector
	*/
	static Matrix3x3 scale(Vector2);

	/**
	* returns a transformation matrix for translating, rotating and scaling by the given
	*/
	static Matrix3x3 TRS(Vector2, float, Vector2);

	float a();
	float b();
	float c();
	float d();
	float e();
	float f();
	float g();
	float h();
	float i();

	Matrix3x3(float, float, float, float, float, float, float, float, float);

	Matrix3x3(std::array<float, 9>);

	Matrix3x3(std::vector<float>);

	std::array<float, 9> getValues();

	float getValue(unsigned int, unsigned int);

	Matrix3x3 transpose();

	float det();

	Matrix3x3 operator*(Matrix3x3);

	Matrix3x3 operator*(float);

	Matrix3x3 operator/(float);

	Vector3 operator*(Vector3*);
};