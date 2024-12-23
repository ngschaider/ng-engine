#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

float Vector2::x() const {
	return this->_x; 
}

float Vector2::y() const {
	return this->_y; 
}

Vector2::Vector2(float x, float y) : _x(x), _y(y){
}

Vector2 Vector2::operator+(Vector2 v) {
	return Vector2(this->x() + v.x(), this->y() + v.y());
}

Vector2 Vector2::operator-(Vector2 v) {
	return Vector2(this->x() - v.x(), this->y() - v.y());
}

Vector2 Vector2::operator*(float v) {
	float mag = this->magnitude() * v;
	float angle = this->angle();
	return Vector2(mag * cosf(angle), mag * sinf(angle));
}

Vector2 Vector2::operator/(float v) {
	float mag = this->magnitude() / v;
	float angle = this->angle();
	return Vector2(mag * cosf(angle), mag * sinf(angle));
}

Vector2 Vector2::operator-() {
	return Vector2(-this->x(), -this->y());
}

Vector3 Vector2::toVector3(float z) {
	return Vector3(this->x(), this->y(), z);
}

Vector4 Vector2::toVector4(float z, float w) {
	return Vector4(this->x(), this->y(), z, w);
}

float Vector2::magnitudeSquared() {
	return this->x() * this->x() + this->y() * this->y();
}

float Vector2::magnitude() {
	return sqrtf(this->magnitudeSquared());
}

float Vector2::angle() {
	return atan2f(this->y(), this->x());
}

float Vector2::distanceSquared(Vector2 v) {
	return (v - *this).magnitudeSquared();
}

float Vector2::distance(Vector2 v) {
	return (v - *this).magnitude();
}

float Vector2::dot(Vector2 v) {
	return this->x() * v.x() + this->y() * v.y();
}

Vector2 operator*(float scalar, Vector2 vector) {
	return vector * scalar;
}

Vector2 operator/(float scalar, Vector2 vector) {
	return Vector2(scalar / vector.x(), scalar / vector.y());
}

Vector2 Vector2::normal() {
	return Vector2(-this->y(), this->x());
}

Vector2 Vector2::normalized() {
	return (*this) / this->magnitude();
}