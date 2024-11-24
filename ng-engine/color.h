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

	Color(int r, int g, int b) {
		this->_r = r;
		this->_g = g;
		this->_b = b;
	}

	float r() const { return this->_r; }
	float g() const { return this->_g; }
	float b() const { return this->_b; }
};