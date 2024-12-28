#include "numbers.h"
#include <cstdlib>
#include <ctime>

bool Random::seeded;

float Random::rand() {
	if (!Random::seeded) {
		std::srand(std::time(nullptr));
		Random::seeded = true;
	}
	return (float) std::rand() / RAND_MAX;
}

float Random::rand(float min, float max) {
	float value = Random::rand();
	return value * (max - min) + min;
}

int Random::randInt(int min, int max) {
	return (int)(Random::rand(min, max));
}