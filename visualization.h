#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "algorithms.h"
#include <vector>

void displayMovementPath(const SimulationResult& result, int initialHead,
                         int diskSize);
void displayDashboard(const std::vector<SimulationResult>& results,
                      std::size_t requestCount);

#endif
