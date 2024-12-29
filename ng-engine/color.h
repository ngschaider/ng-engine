#pragma once

/**
* Represents a color
*/
class Color {
private:
	/**
	* The value of the red channel. Value must be between zero and 255.
	*/
	unsigned int _r;

	/**
	* The value of the green channel. Value must be between zero and 255.
	*/
	unsigned int _g;

	/**
	* The value of the blue channel. Value must be between zero and 255.
	*/
	unsigned int _b;
public:
	/**
	* Returns an instance representing white (255, 255, 255).
	*/
	static Color white() { return Color(255, 255, 255); }

	/**
	* Returns an instance representing black (0, 0, 0).
	*/
	static Color black() { return Color(0, 0, 0); }

	/**
	* Returns an instance representing red (255, 0, 0).
	*/
	static Color red() { return Color(255, 0, 0); }

	/**
	* Returns an instance representing green (0, 255, 0).
	*/
	static Color green() { return Color(0, 255, 0); }

	/**
	* Returns an instance representing blue (0, 0, 255).
	*/
	static Color blue() { return Color(0, 0, 255); }

	/**
	* Constructs a new color from red-green-blue values
	*/
	Color(unsigned int r, unsigned int g, unsigned int b);

	/**
	* Getter for red channel's value
	*/
	unsigned int r() const;

	/**
	* Getter for green channel's value
	*/
	unsigned int g() const;

	/**
	* Getter for blue channel's value
	*/
	unsigned int b() const;
};