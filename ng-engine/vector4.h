#pragma once

#include "vector3.h"
#include "vector2.h"

/**
* A vector of length 4.
*/
class Vector4 {
private:
	/**
	* The x-value of the vector.
	*/
	float _x;

	/**
	* The y-value of the vector.
	*/
	float _y;

	/**
	* The z-value of the vector.
	*/
	float _z;

	/**
	* The w-value of the vector.
	*/
	float _w;
public:
	/**
	* Constructs a new vector [x, y, z, w] from the given values
	*/
	Vector4(float x, float y, float z, float w);

	/**
	* Returns the 1st component of the vector
	* x y z w
	*/
	float x() const;

	/**
	* Returns the 2nd component of the vector
	* x y z w
	*/
	float y() const;

	/**
	* Returns the 3rd component of the vector
	* x y z w
	*/
	float z() const;

	/**
	* Returns the 4th component of the vector
	* x y z w
	*/
	float w() const;

	/**
	* Multiplies this vector by a given value (element-wise) and returns the result as a new vector
	*/
	Vector4 operator*(float v);

	/**
	* Divides this vector through a given value (element-wise) and returns the result as a new vector
	*/
	Vector4 operator/(float v);

	/**
	* Negates the vector
	*/
	Vector4 operator-();

#pragma region Vector2 Conversion Methods
	/**
	* Returns a new Vector2 with the values of this vector's x and x components
	*/
	Vector2 xx() const;

	/**
	* Returns a new Vector2 with the values of this vector's x and y components
	*/
	Vector2 xy() const;

	/**
	* Returns a new Vector2 with the values of this vector's x and z components
	*/
	Vector2 xz() const;

	/**
	* Returns a new Vector2 with the values of this vector's y and x components
	*/
	Vector2 yx() const;

	/**
	* Returns a new Vector2 with the values of this vector's y and y components
	*/
	Vector2 yy() const;

	/**
	* Returns a new Vector2 with the values of this vector's y and z components
	*/
	Vector2 yz() const;

	/**
	* Returns a new Vector2 with the values of this vector's z and x components
	*/
	Vector2 zx() const;

	/**
	* Returns a new Vector2 with the values of this vector's z and y components
	*/
	Vector2 zy() const;

	/**
	* Returns a new Vector2 with the values of this vector's z and z components
	*/
	Vector2 zz() const;
#pragma endregion


#pragma region Vector3 Conversion Methods
	/**
	* Returns a new Vector3 with the values of this vector's x, x and x components
	*/
	Vector3 xxx() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, x and y components
	*/
	Vector3 xxy() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, x and z components
	*/
	Vector3 xxz() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, x and w components
	*/
	Vector3 xxw() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, y and x components
	*/
	Vector3 xyx() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, y and y components
	*/
	Vector3 xyy() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, y and z components
	*/
	Vector3 xyz() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, y and w components
	*/
	Vector3 xyw() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, z and x components
	*/
	Vector3 xzx() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, z and y components
	*/
	Vector3 xzy() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, z and z components
	*/
	Vector3 xzz() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, z and w components
	*/
	Vector3 xzw() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, w and x components
	*/
	Vector3 xwx() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, w and y components
	*/
	Vector3 xwy() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, w and z components
	*/
	Vector3 xwz() const;

	/**
	* Returns a new Vector3 with the values of this vector's x, w and w components
	*/
	Vector3 xww() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, x and x components
	*/
	Vector3 yxx() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, x and y components
	*/
	Vector3 yxy() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, x and z components
	*/
	Vector3 yxz() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, x and w components
	*/
	Vector3 yxw() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, y and x components
	*/
	Vector3 yyx() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, y and y components
	*/
	Vector3 yyy() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, y and z components
	*/
	Vector3 yyz() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, y and w components
	*/
	Vector3 yyw() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, z and z components
	*/
	Vector3 yzx() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, z and y components
	*/
	Vector3 yzy() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, z and z components
	*/
	Vector3 yzz() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, z and z components
	*/
	Vector3 yzw() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, z and z components
	*/
	Vector3 ywx() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, z and z components
	*/
	Vector3 ywy() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, z and z components
	*/
	Vector3 ywz() const;

	/**
	* Returns a new Vector3 with the values of this vector's y, z and z components
	*/
	Vector3 yww() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, x and x components
	*/
	Vector3 zxx() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, x and y components
	*/
	Vector3 zxy() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, x and z components
	*/
	Vector3 zxz() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, x and w components
	*/
	Vector3 zxw() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, y and x components
	*/
	Vector3 zyx() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, y and y components
	*/
	Vector3 zyy() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, y and z components
	*/
	Vector3 zyz() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, y and w components
	*/
	Vector3 zyw() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, z and x components
	*/
	Vector3 zzx() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, z and y components
	*/
	Vector3 zzy() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, z and z components
	*/
	Vector3 zzz() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, z and w components
	*/
	Vector3 zzw() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, w and x components
	*/
	Vector3 zwx() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, w and y components
	*/
	Vector3 zwy() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, w and z components
	*/
	Vector3 zwz() const;

	/**
	* Returns a new Vector3 with the values of this vector's z, w and w components
	*/
	Vector3 zww() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, x and x components
	*/
	Vector3 wxx() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, x and y components
	*/
	Vector3 wxy() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, x and z components
	*/
	Vector3 wxz() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, x and w components
	*/
	Vector3 wxw() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, y and x components
	*/
	Vector3 wyx() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, y and y components
	*/
	Vector3 wyy() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, y and z components
	*/
	Vector3 wyz() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, y and w components
	*/
	Vector3 wyw() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, z and x components
	*/
	Vector3 wzx() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, z and y components
	*/
	Vector3 wzy() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, z and z components
	*/
	Vector3 wzz() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, z and w components
	*/
	Vector3 wzw() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, z and w components
	*/
	Vector3 wwx() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, z and w components
	*/
	Vector3 wwy() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, z and w components
	*/
	Vector3 wwz() const;

	/**
	* Returns a new Vector3 with the values of this vector's w, z and w components
	*/
	Vector3 www() const;
#pragma endregion
};