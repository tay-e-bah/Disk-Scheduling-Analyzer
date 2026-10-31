#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
#include <vector>

enum class Direction { Left, Right };

struct SimulationResult {
    std::string algorithmName;
    std::vector<int> headPath; // Service order, including boundary/wrap travel where applicable.
    long long totalMovement = 0;
};

SimulationResult runFCFS(int initialHead, const std::vector<int>& requests);
SimulationResult runSSTF(int initialHead, const std::vector<int>& requests);
SimulationResult runSCAN(int initialHead, const std::vector<int>& requests,
                         int diskSize, Direction direction);
SimulationResult runCSCAN(int initialHead, const std::vector<int>& requests,
                          int diskSize, Direction direction);
SimulationResult runLOOK(int initialHead, const std::vector<int>& requests,
                         Direction direction);

#endif
