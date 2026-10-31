#include "visualization.h"
#include "calculations.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

void displayMovementPath(const SimulationResult& result, int initialHead,
                         int diskSize) {
    std::cout << "\n========== MOVEMENT VISUALIZATION: "
              << result.algorithmName << " ==========\n";
    std::cout << "Head path: " << initialHead;
    for (int p : result.headPath) std::cout << " -> " << p;
    std::cout << "\n\nCylinder scale (0 to " << diskSize - 1 << "):\n";

    // A compact horizontal scale. Each visited cylinder is mapped to one
    // of 60 columns; labels remain in the exact path above.
    const int width = 60;
    std::string line(width, '-');
    auto columnFor = [diskSize, width](int cylinder) {
        if (diskSize <= 1) return 0;
        return (cylinder * (width - 1)) / (diskSize - 1);
    };

    std::vector<int> visited;
    visited.push_back(initialHead);
    for (int p : result.headPath) visited.push_back(p);

    for (std::size_t i = 0; i < visited.size(); ++i) {
        int col = columnFor(visited[i]);
        line[col] = '*';
    }

    std::cout << "0 |" << line << "| " << diskSize - 1 << "\n";
    std::cout << "    * = visited cylinder (positions may overlap on this compact scale)\n";
    std::cout << "Total head movement: " << result.totalMovement << " cylinders\n";
}

void displayDashboard(const std::vector<SimulationResult>& results,
                      std::size_t requestCount) {
    std::cout << "\n================ PERFORMANCE DASHBOARD ================\n";
    if (results.empty()) {
        std::cout << "No analysis results available.\n";
        return;
    }

    long long baseline = results.front().totalMovement;
    long long bestValue = results.front().totalMovement;
    std::string bestName = results.front().algorithmName;
    long long maxValue = 1;

    for (const auto& r : results) {
        if (r.totalMovement < bestValue) {
            bestValue = r.totalMovement;
            bestName = r.algorithmName;
        }
        maxValue = std::max(maxValue, r.totalMovement);
    }

    for (const auto& r : results) {
        const int barLength = static_cast<int>((r.totalMovement * 35) / maxValue);
        std::cout << std::left << std::setw(8) << r.algorithmName << " | ";
        for (int i = 0; i < barLength; ++i) std::cout << '#';
        std::cout << " " << r.totalMovement << " cylinders";

        if (r.algorithmName != "FCFS") {
            std::cout << " | improvement vs FCFS: "
                      << std::fixed << std::setprecision(2)
                      << calculateImprovement(baseline, r.totalMovement) << "%";
        }
        std::cout << "\n";
    }

    std::cout << "\nBest result for this input: " << bestName
              << " (" << bestValue << " cylinders)\n";
    std::cout << "Average movement is total movement divided by "
              << requestCount << " requests.\n";
    std::cout << "Note: Lowest movement is not the only measure of real-world disk performance.\n";
}
