#pragma once

class Vector4 {
private:
	float _x;
	float _y;
	float _z;
	float _w;
public:
	Vector4() : Vector4(0, 0, 0, 0) {

	}

	Vector4(float x, float y, float z, float w) {
		this->_x = x;
		this->_y = y;
		this->_z = y;
		this->_w = y;
	}

	float x() const { return this->_x; }
	float y() const { return this->_y; }
	float z() const { return this->_z; }
	float w() const { return this->_w; }

	Vector4 operator*(float v) {
		return Vector4(this->x() * v, this->y() * v, this->z() * v, this->w() * v);
	}
	Vector4 operator/(float v) {
		return Vector4(this->x() / v, this->y() / v, this->z() / v, this->w() / v);
	}
};