#pragma once

#include "vector4.h"
#include "vector2.h"
#include "vector3.h"

Vector4::Vector4(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {
}

float Vector4::x() const {
	return this->_x; 
}

float Vector4::y() const {
	return this->_y; 
}

float Vector4::z() const {
	return this->_z; 
}

float Vector4::w() const {
	return this->_w; 
}

Vector4 Vector4::operator*(float v) {
	return Vector4(this->x() * v, this->y() * v, this->z() * v, this->w() * v);
}

Vector4 Vector4::operator/(float v) {
	return Vector4(this->x() / v, this->y() / v, this->z() / v, this->w() / v);
}

Vector4 Vector4::operator-() {
	return Vector4(-this->x(), -this->y(), -this->z(), -this->w());
}

#pragma region Vector2 Conversion Methods
Vector2 Vector4::xx() const {
	return Vector2(this->x(), this->x());
}

Vector2 Vector4::xy() const {
	return Vector2(this->x(), this->y());
}

Vector2 Vector4::xz() const {
	return Vector2(this->x(), this->z());
}

Vector2 Vector4::yx() const {
	return Vector2(this->y(), this->x());
}

Vector2 Vector4::yy() const {
	return Vector2(this->y(), this->y());
}

Vector2 Vector4::yz() const {
	return Vector2(this->y(), this->z());
}

Vector2 Vector4::zx() const {
	return Vector2(this->z(), this->x());
}

Vector2 Vector4::zy() const {
	return Vector2(this->z(), this->y());
}

Vector2 Vector4::zz() const {
	return Vector2(this->z(), this->z());
}
#pragma endregion

#pragma region Vector3 Conversion Methods
Vector3 Vector4::xxx() const {
	return Vector3(this->x(), this->x(), this->x());
}

Vector3 Vector4::xxy() const {
	return Vector3(this->x(), this->x(), this->y());
}

Vector3 Vector4::xxz() const {
	return Vector3(this->x(), this->x(), this->z());
}

Vector3 Vector4::xxw() const {
	return Vector3(this->x(), this->x(), this->w());
}

Vector3 Vector4::xyx() const {
	return Vector3(this->x(), this->y(), this->x());
}

Vector3 Vector4::xyy() const {
	return Vector3(this->x(), this->y(), this->y());
}

Vector3 Vector4::xyz() const {
	return Vector3(this->x(), this->y(), this->z());
}

Vector3 Vector4::xyw() const {
	return Vector3(this->x(), this->y(), this->w());
}

Vector3 Vector4::xzx() const {
	return Vector3(this->x(), this->z(), this->x());
}

Vector3 Vector4::xzy() const {
	return Vector3(this->x(), this->z(), this->y());
}

Vector3 Vector4::xzz() const {
	return Vector3(this->x(), this->z(), this->z());
}

Vector3 Vector4::xzw() const {
	return Vector3(this->x(), this->z(), this->w());
}

Vector3 Vector4::xwx() const {
	return Vector3(this->x(), this->w(), this->x());
}

Vector3 Vector4::xwy() const {
	return Vector3(this->x(), this->w(), this->y());
}

Vector3 Vector4::xwz() const {
	return Vector3(this->x(), this->w(), this->z());
}

Vector3 Vector4::xww() const {
	return Vector3(this->x(), this->w(), this->w());
}

Vector3 Vector4::yxx() const {
	return Vector3(this->y(), this->x(), this->x());
}

Vector3 Vector4::yxy() const {
	return Vector3(this->y(), this->x(), this->y());
}

Vector3 Vector4::yxz() const {
	return Vector3(this->y(), this->x(), this->z());
}

Vector3 Vector4::yxw() const {
	return Vector3(this->y(), this->x(), this->w());
}

Vector3 Vector4::yyx() const {
	return Vector3(this->y(), this->y(), this->x());
}

Vector3 Vector4::yyy() const {
	return Vector3(this->y(), this->y(), this->y());
}

Vector3 Vector4::yyz() const {
	return Vector3(this->y(), this->y(), this->z());
}

Vector3 Vector4::yyw() const {
	return Vector3(this->y(), this->y(), this->w());
}

Vector3 Vector4::yzx() const {
	return Vector3(this->y(), this->z(), this->x());
}

Vector3 Vector4::yzy() const {
	return Vector3(this->y(), this->z(), this->y());
}

Vector3 Vector4::yzz() const {
	return Vector3(this->y(), this->z(), this->z());
}

Vector3 Vector4::yzw() const {
	return Vector3(this->y(), this->z(), this->w());
}

Vector3 Vector4::ywx() const {
	return Vector3(this->y(), this->w(), this->x());
}

Vector3 Vector4::ywy() const {
	return Vector3(this->y(), this->w(), this->y());
}

Vector3 Vector4::ywz() const {
	return Vector3(this->y(), this->w(), this->z());
}

Vector3 Vector4::yww() const {
	return Vector3(this->y(), this->w(), this->w());
}

Vector3 Vector4::zxx() const {
	return Vector3(this->z(), this->x(), this->x());
}

Vector3 Vector4::zxy() const {
	return Vector3(this->z(), this->x(), this->y());
}

Vector3 Vector4::zxz() const {
	return Vector3(this->z(), this->x(), this->z());
}

Vector3 Vector4::zxw() const {
	return Vector3(this->z(), this->x(), this->w());
}

Vector3 Vector4::zyx() const {
	return Vector3(this->z(), this->y(), this->x());
}

Vector3 Vector4::zyy() const {
	return Vector3(this->z(), this->y(), this->y());
}

Vector3 Vector4::zyz() const {
	return Vector3(this->z(), this->y(), this->z());
}

Vector3 Vector4::zyw() const {
	return Vector3(this->z(), this->y(), this->w());
}

Vector3 Vector4::zzx() const {
	return Vector3(this->z(), this->z(), this->x());
}

Vector3 Vector4::zzy() const {
	return Vector3(this->z(), this->z(), this->y());
}

Vector3 Vector4::zzz() const {
	return Vector3(this->z(), this->z(), this->z());
}

Vector3 Vector4::zzw() const {
	return Vector3(this->z(), this->z(), this->w());
}

Vector3 Vector4::zwx() const {
	return Vector3(this->z(), this->w(), this->x());
}

Vector3 Vector4::zwy() const {
	return Vector3(this->z(), this->w(), this->y());
}

Vector3 Vector4::zwz() const {
	return Vector3(this->z(), this->w(), this->z());
}

Vector3 Vector4::zww() const {
	return Vector3(this->z(), this->w(), this->w());
}

Vector3 Vector4::wxx() const {
	return Vector3(this->w(), this->x(), this->x());
}

Vector3 Vector4::wxy() const {
	return Vector3(this->w(), this->x(), this->y());
}

Vector3 Vector4::wxz() const {
	return Vector3(this->w(), this->x(), this->z());
}

Vector3 Vector4::wxw() const {
	return Vector3(this->w(), this->x(), this->w());
}

Vector3 Vector4::wyx() const {
	return Vector3(this->w(), this->y(), this->x());
}

Vector3 Vector4::wyy() const {
	return Vector3(this->w(), this->y(), this->y());
}

Vector3 Vector4::wyz() const {
	return Vector3(this->w(), this->y(), this->z());
}

Vector3 Vector4::wyw() const {
	return Vector3(this->w(), this->y(), this->w());
}

Vector3 Vector4::wzx() const {
	return Vector3(this->w(), this->z(), this->x());
}

Vector3 Vector4::wzy() const {
	return Vector3(this->w(), this->z(), this->y());
}

Vector3 Vector4::wzz() const {
	return Vector3(this->w(), this->z(), this->z());
}

Vector3 Vector4::wzw() const {
	return Vector3(this->w(), this->z(), this->w());
}

Vector3 Vector4::wwx() const {
	return Vector3(this->w(), this->w(), this->x());
}

Vector3 Vector4::wwy() const {
	return Vector3(this->w(), this->w(), this->y());
}

Vector3 Vector4::wwz() const {
	return Vector3(this->w(), this->w(), this->z());
}

Vector3 Vector4::www() const {
	return Vector3(this->w(), this->w(), this->w());
}
#pragma endregion 