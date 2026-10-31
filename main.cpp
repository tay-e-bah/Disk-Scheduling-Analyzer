#include "algorithms.h"
#include "calculations.h"
#include "history.h"
#include "visualization.h"

#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

using namespace std;

int readInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) return value;
        cout << "Invalid input. Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

Direction readDirection() {
    cout << "\nInitial direction for SCAN-family algorithms:\n";
    cout << "1. Left\n2. Right\n";
    int choice = readInteger("Choose direction: ");
    while (choice != 1 && choice != 2) {
        cout << "Please choose 1 or 2.\n";
        choice = readInteger("Choose direction: ");
    }
    return choice == 1 ? Direction::Left : Direction::Right;
}

vector<int> readManualRequests(int diskSize) {
    int count = readInteger("Enter number of disk requests: ");
    while (count < 0 || count > 10000) {
        cout << "Enter a request count between 0 and 10000.\n";
        count = readInteger("Enter number of disk requests: ");
    }

    vector<int> requests;
    requests.reserve(static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        int request = readInteger("Enter request " + to_string(i + 1) + ": ");
        while (request < 0 || request >= diskSize) {
            cout << "Request must be between 0 and " << diskSize - 1 << ".\n";
            request = readInteger("Enter request " + to_string(i + 1) + ": ");
        }
        requests.push_back(request);
    }
    return requests;
}

vector<int> generateRandomRequests(int diskSize) {
    int count = readInteger("How many random requests should be generated? ");
    while (count < 1 || count > 10000) {
        cout << "Enter a number between 1 and 10000.\n";
        count = readInteger("How many random requests should be generated? ");
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, diskSize - 1);

    vector<int> requests;
    for (int i = 0; i < count; ++i) requests.push_back(distribution(generator));

    cout << "\nGenerated requests:\n";
    for (size_t i = 0; i < requests.size(); ++i) {
        cout << requests[i] << (i + 1 == requests.size() ? "\n" : ", ");
    }
    return requests;
}

vector<SimulationResult> runAllAlgorithms(int head, const vector<int>& requests,
                                          int diskSize, Direction direction) {
    vector<SimulationResult> results;
    results.push_back(runFCFS(head, requests));
    results.push_back(runSSTF(head, requests));
    results.push_back(runSCAN(head, requests, diskSize, direction));
    results.push_back(runCSCAN(head, requests, diskSize, direction));
    results.push_back(runLOOK(head, requests, direction));
    return results;
}

void showResults(const vector<SimulationResult>& results, size_t requestCount) {
    cout << "\n================ DETAILED RESULTS ================\n";
    long long fcfsMovement = results.empty() ? 0 : results.front().totalMovement;

    for (const auto& r : results) {
        cout << "\n" << r.algorithmName << "\n";
        cout << "Path: ";
        if (r.headPath.empty()) cout << "(no requests)";
        else {
            for (size_t i = 0; i < r.headPath.size(); ++i) {
                if (i) cout << " -> ";
                cout << r.headPath[i];
            }
        }
        cout << "\nTotal head movement: " << r.totalMovement;
        cout << "\nAverage per request: "
             << calculateAverageMovement(r.totalMovement, requestCount);
        if (r.algorithmName != "FCFS") {
            cout << "\nImprovement vs FCFS: "
                 << calculateImprovement(fcfsMovement, r.totalMovement) << "%";
        }
        cout << "\n";
    }
}

void analyze(bool useRandomRequests) {
    cout << "\n========== DISK INPUT ==========\n";
    int diskSize = readInteger("Number of cylinders (minimum 2): ");
    while (diskSize < 2 || diskSize > 1000000) {
        cout << "Disk size must be between 2 and 1000000.\n";
        diskSize = readInteger("Number of cylinders (minimum 2): ");
    }

    int head = readInteger("Initial head position: ");
    while (head < 0 || head >= diskSize) {
        cout << "Head must be between 0 and " << diskSize - 1 << ".\n";
        head = readInteger("Initial head position: ");
    }

    vector<int> requests = useRandomRequests
        ? generateRandomRequests(diskSize)
        : readManualRequests(diskSize);

    Direction direction = readDirection();
    vector<SimulationResult> results =
        runAllAlgorithms(head, requests, diskSize, direction);

    showResults(results, requests.size());
    displayDashboard(results, requests.size());

    cout << "\nChoose an algorithm to visualize:\n";
    cout << "1. FCFS  2. SSTF  3. SCAN  4. C-SCAN  5. LOOK\n";
    int choice = readInteger("Selection (1-5, 0 to skip): ");
    if (choice >= 1 && choice <= 5) {
        displayMovementPath(results[static_cast<size_t>(choice - 1)], head, diskSize);
    }

    cout << "\nSave this analysis to history.txt? (1 = Yes, 0 = No): ";
    int saveChoice = readInteger("");
    if (saveChoice == 1) {
        saveHistory(results, diskSize, head, requests, direction);
    }
}

int main() {
    cout << "====================================================\n";
    cout << "       DISK SCHEDULING & PERFORMANCE ANALYZER       \n";
    cout << "====================================================\n";

    while (true) {
        cout << "\nMAIN MENU\n";
        cout << "1. Run analysis (manual requests)\n";
        cout << "2. Generate random requests and analyze\n";
        cout << "3. View saved analysis history\n";
        cout << "4. Exit\n";

        int choice = readInteger("Choose: ");
        switch (choice) {
            case 1: analyze(false); break;
            case 2: analyze(true); break;
            case 3: showHistory(); break;
            case 4:
                cout << "Thank you for using the analyzer.\n";
                return 0;
            default:
                cout << "Invalid choice. Please select 1-4.\n";
        }
    }
}
