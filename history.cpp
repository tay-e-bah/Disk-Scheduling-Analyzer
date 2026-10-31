#include "history.h"

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

void saveHistory(const std::vector<SimulationResult>& results,
                 int diskSize, int initialHead, const std::vector<int>& requests,
                 Direction direction) {
    std::ofstream file("history.txt", std::ios::app);
    if (!file) {
        std::cout << "Could not open history.txt for writing.\n";
        return;
    }

    std::time_t now = std::time(nullptr);
    file << "====================================================\n";
    file << "Analysis date: " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "\n";
    file << "Disk size: " << diskSize << " | Initial head: " << initialHead
         << " | Direction: " << (direction == Direction::Right ? "Right" : "Left") << "\n";
    file << "Requests: ";
    for (std::size_t i = 0; i < requests.size(); ++i) {
        if (i) file << ", ";
        file << requests[i];
    }
    file << "\n";

    for (const auto& r : results) {
        file << r.algorithmName << " | Total movement: " << r.totalMovement << " | Path: ";
        file << initialHead;
        for (int p : r.headPath) file << " -> " << p;
        file << "\n";
    }
    file << "\n";
    std::cout << "Analysis saved to history.txt.\n";
}

void showHistory() {
    std::ifstream file("history.txt");
    if (!file) {
        std::cout << "\nNo history found yet. Run an analysis and save it first.\n";
        return;
    }

    std::cout << "\n================ SAVED ANALYSIS HISTORY ================\n";
    std::string line;
    while (std::getline(file, line)) std::cout << line << "\n";
}
