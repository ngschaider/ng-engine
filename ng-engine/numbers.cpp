#include <chrono>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <random>
#include "numbers.h"

std::mt19937 Random::gen;

void Random::seed() {
    std::random_device rd;
    // seed value designed specifically to be different across app executions
    std::mt19937::result_type seed = rd() ^ (
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count() +
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count());

    Random::gen = std::mt19937(seed);
}

float Random::rand() {
    return Random::rand(0, 1);
}

float Random::rand(float min, float max) {
    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(Random::gen);
}

int Random::randInt(int min, int max) {
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(Random::gen);
}