#pragma once

#include <math.h>

/**
* Represents a 2-dimensional vector
*/
class Vector2 {
private:
	float _x;
	float _y;
public:
	float x() const { return this->_x; }
	float y() const { return this->_y; }

	Vector2(float x, float y) {
		this->_x = x;
		this->_y = y;
	}

	Vector2() {
		this->_x = 0;
		this->_y = 0;
	}
	
	Vector2 operator+(Vector2 v) {
		return Vector2(this->x() + v.x(), this->y() + v.y());
	}

	Vector2 operator-(Vector2 v) {
		return Vector2(this->x() - v.x(), this->y() - v.y());
	}

	Vector2 operator*(float v) {
		float mag = this->magnitude() * v;
		float angle = this->angle();
		return Vector2(mag * cosf(angle), mag * sinf(angle));
	}

	Vector2 operator/(float v) {
		float mag = this->magnitude() / v;
		float angle = this->angle();
		return Vector2(mag * cosf(angle), mag * sinf(angle));
	}

	float magnitudeSquared() {
		return this->x() * this->x() + this->y() + this->y();
	}

	float magnitude() {
		return sqrtf(this->magnitudeSquared());
	}

	float angle() {
		return atan2f(this->y(), this->x());
	}

	float distanceSquared(Vector2 v) {
		return (v - *this).magnitudeSquared();
	}

	float distance(Vector2 v) {
		return (v - *this).magnitude();
	}
};