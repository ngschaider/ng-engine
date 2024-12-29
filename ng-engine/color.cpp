#include "color.h"
#include <cassert>

Color::Color(unsigned int r, unsigned int g, unsigned int b) {
	this->_r = r;
	this->_g = g;
	this->_b = b;
}

unsigned int Color::r() const {
	assert(this->_r >= 0);
	assert(this->_r <= 255);
	return this->_r;
}

unsigned int Color::g() const {
	assert(this->_g >= 0);
	assert(this->_g <= 255);
	return this->_g;
}

unsigned int Color::b() const {
	assert(this->_b >= 0);
	assert(this->_b <= 255);
	return this->_b;
}
