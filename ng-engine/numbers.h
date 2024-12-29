#pragma once

/**
* Mathematical constant PI.
*/
constexpr inline float PI = 3.14159264f;

/**
* Factor to convert from degrees to radiants.
*/
constexpr inline float DEG2RAD = PI / 180;

/**
* Factor to convert from radiants to degrees.
*/
constexpr inline float RAD2DEG = 180 / PI;

/**
* Utility class for generating random numbers.
*/
class Random {
private:
	/**
	* Wether the PRNG has already been seeded or not.
	*/
	static bool seeded;
public:
	/**
	* Returns a pseudo-random number between zero and one.
	*/
	static float rand();

	/**
	* Returns a pseudo-random number between the specified minimum and maximum.
	*/
	static float rand(float min, float max);

	/**
	* Returns a pseudo-random number between the specified minimum and maximum.
	*/
	static int randInt(int min, int max);
};