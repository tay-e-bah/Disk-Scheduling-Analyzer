#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <cstddef>

double calculateAverageMovement(long long totalMovement, std::size_t requestCount);
double calculateImprovement(long long baselineMovement, long long comparedMovement);

#endif
