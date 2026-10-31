#ifndef HISTORY_H
#define HISTORY_H

#include "algorithms.h"
#include <vector>

void saveHistory(const std::vector<SimulationResult>& results,
                 int diskSize, int initialHead, const std::vector<int>& requests,
                 Direction direction);
void showHistory();

#endif
