#pragma once

#include "math.h"

class Vector3 {
private:
	float _x;
	float _y;
	float _z;

public:
	Vector3(float x, float y, float z) {
		this->_x = x;
		this->_y = y;
		this->_z = z;
	}

	float x() const { return this->_x; }
	float y() const { return this->_y; }
	float z() const { return this->_z; }

	float magnitudeSquared() {
		return this->x() * this->x() + this->y() * this->y() + this->z() * this->z();
	}

	float magnitude() {
		return sqrtf(this->magnitudeSquared());
	}

	bool operator==(Vector3 v) {
		return this->x() == v.x() && this->y() == v.y() && this->z() == v.z();
	}

	Vector3 operator+(Vector3 v) {
		return Vector3(this->x() + v.x(), this->y() + v.y(), this->z() + v.z());
	}
	Vector3 operator*(float v) {
		return Vector3(this->x() * v, this->y() * v, this->z() * v);
	}
	Vector3 operator/(float v) {
		return Vector3(this->x() / v, this->y() / v, this->z() / v);
	}

	float dot(Vector3 v) {
		return this->x() * v.x()
			+ this->y() * v.y()
			+ this->z() * v.z();
	}
};