#pragma once

class Color {
private:
	unsigned int _r;
	unsigned int _g;
	unsigned int _b;
public:
	static Color white() { return Color(255, 255, 255); }
	static Color black() { return Color(0, 0, 0); }
	static Color red() { return Color(255, 0, 0); }
	static Color green() { return Color(0, 255, 0); }
	static Color blue() { return Color(0, 0, 255); }

	Color(unsigned int, unsigned int, unsigned int);

	unsigned int r() const { return this->_r; }
	unsigned int g() const { return this->_g; }
	unsigned int b() const { return this->_b; }
};