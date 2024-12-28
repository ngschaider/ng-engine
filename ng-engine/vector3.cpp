#include "vector3.h"
#include "vector4.h"
#include "numbers.h"

Vector3::Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {
}

float Vector3::x() const {
	return this->_x;
}

float Vector3::y() const {
	return this->_y;
}

float Vector3::z() const {
	return this->_z;
}

float Vector3::magnitudeSquared() const {
	return this->x() * this->x() + this->y() * this->y() + this->z() * this->z();
}

float Vector3::magnitude() const {
	return sqrtf(this->magnitudeSquared());
}

bool Vector3::operator==(Vector3 v) {
	return this->x() == v.x() && this->y() == v.y() && this->z() == v.z();
}

Vector3 Vector3::operator+(Vector3 v) {
	return Vector3(this->x() + v.x(), this->y() + v.y(), this->z() + v.z());
}

Vector3 Vector3::operator*(float v) {
	return Vector3(this->x() * v, this->y() * v, this->z() * v);
}

Vector3 Vector3::operator/(float v) {
	return Vector3(this->x() / v, this->y() / v, this->z() / v);
}

Vector3 Vector3::operator-() {
	return Vector3(-this->x(), -this->y(), -this->z());
}

Vector3 Vector3::operator-(Vector3 v) {
	return Vector3(this->x() - v.x(), this->y() - v.y(), this->z() - v.z());
}

float Vector3::dot(Vector3 v) const {
	return this->x() * v.x()
		+ this->y() * v.y()
		+ this->z() * v.z();
}

Vector2 Vector3::xx() const {
	return Vector2(this->x(), this->x());
}

Vector2 Vector3::xy() const {
	return Vector2(this->x(), this->y());
}

Vector2 Vector3::xz() const {
	return Vector2(this->x(), this->z());
}

Vector2 Vector3::yx() const {
	return Vector2(this->y(), this->x());
}

Vector2 Vector3::yy() const {
	return Vector2(this->y(), this->y());
}

Vector2 Vector3::yz() const {
	return Vector2(this->y(), this->z());
}

Vector2 Vector3::zx() const {
	return Vector2(this->z(), this->x());
}

Vector2 Vector3::zy() const {
	return Vector2(this->z(), this->y());
}

Vector2 Vector3::zz() const {
	return Vector2(this->z(), this->z());
}

Vector4 Vector3::toVector4(float w) const {
	return Vector4(this->x(), this->y(), this->z(), w);
}

Vector3 operator/(float scalar, Vector3 vec) {
	return Vector3(scalar / vec.x(), scalar / vec.y(), scalar / vec.z());
}