#include "calculations.h"

double calculateAverageMovement(long long totalMovement, std::size_t requestCount) {
    if (requestCount == 0) return 0.0;
    return static_cast<double>(totalMovement) / static_cast<double>(requestCount);
}

double calculateImprovement(long long baselineMovement, long long comparedMovement) {
    if (baselineMovement == 0) return 0.0;
    return (static_cast<double>(baselineMovement - comparedMovement) /
            static_cast<double>(baselineMovement)) * 100.0;
}
