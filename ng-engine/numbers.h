#pragma once

constexpr inline float PI = 3.14159264f;
constexpr inline float DEG2RAD = PI / 180;
constexpr inline float RAD2DEG = 180 / PI;

class Random {
private:
	static bool seeded;
public:
	static float rand();
	static float rand(float min, float max);

	static int randInt(int min, int max);
};