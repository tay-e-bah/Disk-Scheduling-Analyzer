#include "algorithms.h"

#include <algorithm>
#include <cstdlib>

namespace {
long long movementForPath(int start, const std::vector<int>& path) {
    long long total = 0;
    int previous = start;
    for (int position : path) {
        total += std::abs(position - previous);
        previous = position;
    }
    return total;
}

SimulationResult makeResult(const std::string& name, int start,
                            const std::vector<int>& path) {
    SimulationResult result;
    result.algorithmName = name;
    result.headPath = path;
    result.totalMovement = movementForPath(start, path);
    return result;
}

void splitRequests(int head, const std::vector<int>& requests,
                   std::vector<int>& left, std::vector<int>& right) {
    for (int request : requests) {
        if (request < head) left.push_back(request);
        else if (request > head) right.push_back(request);
        // A request exactly at the current head needs no movement.
        // It is included as a service point in FCFS/SSTF; for scan-family
        // algorithms it is already at the head and does not affect travel.
    }
}
}

SimulationResult runFCFS(int initialHead, const std::vector<int>& requests) {
    return makeResult("FCFS", initialHead, requests);
}

SimulationResult runSSTF(int initialHead, const std::vector<int>& requests) {
    std::vector<int> remaining = requests;
    std::vector<int> path;
    int current = initialHead;

    while (!remaining.empty()) {
        std::size_t best = 0;
        int bestDistance = std::abs(remaining[0] - current);
        for (std::size_t i = 1; i < remaining.size(); ++i) {
            int distance = std::abs(remaining[i] - current);
            if (distance < bestDistance) {
                bestDistance = distance;
                best = i;
            }
        }
        current = remaining[best];
        path.push_back(current);
        remaining.erase(remaining.begin() + static_cast<std::ptrdiff_t>(best));
    }
    return makeResult("SSTF", initialHead, path);
}

SimulationResult runSCAN(int initialHead, const std::vector<int>& requests,
                         int diskSize, Direction direction) {
    std::vector<int> left, right, path;
    splitRequests(initialHead, requests, left, right);
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    if (direction == Direction::Right) {
        path.insert(path.end(), right.begin(), right.end());
        if (initialHead != diskSize - 1 &&
            (path.empty() || path.back() != diskSize - 1)) {
            path.push_back(diskSize - 1);
        }
        for (auto it = left.rbegin(); it != left.rend(); ++it) path.push_back(*it);
    } else {
        for (auto it = left.rbegin(); it != left.rend(); ++it) path.push_back(*it);
        if (initialHead != 0 && (path.empty() || path.back() != 0)) path.push_back(0);
        path.insert(path.end(), right.begin(), right.end());
    }
    return makeResult("SCAN", initialHead, path);
}

SimulationResult runCSCAN(int initialHead, const std::vector<int>& requests,
                          int diskSize, Direction direction) {
    std::vector<int> left, right, path;
    splitRequests(initialHead, requests, left, right);
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    if (direction == Direction::Right) {
        path.insert(path.end(), right.begin(), right.end());
        if (path.empty() || path.back() != diskSize - 1) path.push_back(diskSize - 1);
        if (diskSize > 1) path.push_back(0);
        path.insert(path.end(), left.begin(), left.end());
    } else {
        for (auto it = left.rbegin(); it != left.rend(); ++it) path.push_back(*it);
        if (path.empty() || path.back() != 0) path.push_back(0);
        if (diskSize > 1) path.push_back(diskSize - 1);
        for (auto it = right.rbegin(); it != right.rend(); ++it) path.push_back(*it);
    }
    return makeResult("C-SCAN", initialHead, path);
}

SimulationResult runLOOK(int initialHead, const std::vector<int>& requests,
                         Direction direction) {
    std::vector<int> left, right, path;
    splitRequests(initialHead, requests, left, right);
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    if (direction == Direction::Right) {
        path.insert(path.end(), right.begin(), right.end());
        for (auto it = left.rbegin(); it != left.rend(); ++it) path.push_back(*it);
    } else {
        for (auto it = left.rbegin(); it != left.rend(); ++it) path.push_back(*it);
        path.insert(path.end(), right.begin(), right.end());
    }
    return makeResult("LOOK", initialHead, path);
}
