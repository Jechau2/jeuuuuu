#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace Random {
inline int range(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}
} // namespace Random

#endif // RANDOM_H
