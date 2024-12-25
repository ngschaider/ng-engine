#pragma once

#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"
#include "matrix3x3.h"
#include <array>
#include <vector>

/**
* Represents a matrix with 3 rows and 4 columns
*/
class Matrix3x4 {
private:
	std::array<float, 16> values;

	// keep this private as we do not want to modify the matrix after instantiation and
	// this is the only way we can make sure nobody modifies it from the outside!
	void setValue(unsigned int x, unsigned int y, float value);
public:
	/**
	* Returns a 3x4 matrix where the first three columns are those of a 3x3 identity matrix and the last column is a zero vector
	*/
	static Matrix3x4 identity();

	/**
	* Returns a 4x4 transformation matrix that can be used to translate any vector by the given position
	*/
	static Matrix4x4 translate(Vector3 pos);

	/**
	* Returns a 4x4 transformation matrix that can be used to rotate any vector around the x-axis by the given rotation
	*/
	static Matrix4x4 rotateX(float rotation);

	/**
	* Returns a 4x4 transformation matrix that can be used to rotate any vector around the y-axis by the given rotation
	*/
	static Matrix4x4 rotateY(float rotation);

	/**
	* Returns a 4x4 transformation matrix that can be used to rotate any vector around the z-axis by the given rotation
	*/
	static Matrix4x4 rotateZ(float rotation);

	/**
	* Returns a 4x4 transformation matrix that can be used to rotate any vector by the given quaternion
	*/
	static Matrix4x4 rotate(Quaternion q);

	/**
	* Returns a 4x4 transformation matrix that can be used to scale any vector by the given factors
	*/
	static Matrix4x4 scale(Vector3 scale);

	/**
	* Returns a 4x4 orthographics projections matrix
	*/
	static Matrix4x4 orthographic(Vector3 pos, Vector3 size, float near, float far);

	/**
	* Returns a 4x4 transformation matrix that can be used to translate, rotate and scale any vector by the given vectors.
	*/
	static Matrix4x4 TRS(Vector3 pos, Quaternion rotation, Vector3 scaling);

	/**
	* Constructs a new Matrix4x4 instance using the specified values
	*/
	Matrix4x4(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p);

	/**
	* Constructs a new Matrix4x4 instance using the specified values
	*/
	Matrix4x4(std::array<float, 16> values);

	/**
	* Constructs a new Matrix4x4 instance using the specified values.
	* The given vector must have a length of exactly 16.
	*/
	Matrix4x4(std::vector<float> values);

	/**
	* Returns an array of all 16 elements of the array sorted in row major format
	*/
	std::array<float, 16> getValues();

	/**
	* Returns the value of the matrix at row `y` and column `x`
	*/
	float getValue(unsigned int x, unsigned int y);

	/**
	* Returns the 1st value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float a();

	/**
	* Returns the 2nd value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float b();

	/**
	* Returns the 3th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float c();

	/**
	* Returns the 4th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float d();

	/**
	* Returns the 5th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float e();

	/**
	* Returns the 6th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float f();

	/**
	* Returns the 7th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float g();

	/**
	* Returns the 8th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float h();

	/**
	* Returns the 9th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float i();

	/**
	* Returns the 10th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float j();

	/**
	* Returns the 11th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float k();

	/**
	* Returns the 12th value of the matrix:
	* a b c d
	* e f g h
	* i j k l
	*/
	float l();


	/**
	* Multiplies the Matrix4x4 with the given value (element-wise) and returns the result in a new Matrix4x4.
	*/
	Matrix4x4 operator*(float f);

	/**
	* Divides the matrix by the given value (element-wise) and returns the result in a new Matrix4x4.
	*/
	Matrix4x4 operator/(float f);

	/**
	* Multiplies the matrix with another matrix using standard mathematics and returns the result in a new Matrix4x4.
	*/
	Matrix4x4 operator*(Matrix4x4 m);

	/**
	* Multiplies the matrix with a vector of length 4 and returns the result in a new Vector4.
	* One could also call this "applying" the matrix to the vector.
	*/
	Vector4 operator*(Vector4 v);

	/**
	* Returns the determinant of the matrix
	*/
	float det();

	/**
	* Returns the adjugate of this matrix
	*/
	Matrix4x4 adj();

	/**
	* Returns the inverse of this matrix
	*/
	Matrix4x4 invert();
};