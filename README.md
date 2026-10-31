# Disk Scheduling & Performance Analyzer (Upgraded)

A C++11 terminal application that simulates five disk scheduling algorithms and compares their total head movement.

## Features

- Manual disk request input
- Random disk request generator
- FCFS, SSTF, SCAN, C-SCAN, and LOOK algorithms
- Total and average head movement calculations
- Improvement percentage compared with FCFS
- Text-based performance dashboard
- Movement path and compact cylinder-scale visualization
- Save analyses to `history.txt` and view saved history

## Files

- `main.cpp` — menu, input, orchestration, and results
- `algorithms.h/.cpp` — five disk scheduling algorithms
- `calculations.h/.cpp` — average and improvement calculations
- `visualization.h/.cpp` — movement display and dashboard
- `history.h/.cpp` — save and view analysis history

## Requirements

- GCC / MinGW g++ or another C++11-compatible compiler
- VS Code is optional; any editor and terminal will work

## Compile on Windows (MinGW)

Open the terminal in this project folder and run:

```bash
g++ -std=c++11 main.cpp algorithms.cpp calculations.cpp visualization.cpp history.cpp -o analyzer.exe
```

Then run:

```bash
.\analyzer.exe
```

## Compile on Linux / macOS

```bash
g++ -std=c++11 main.cpp algorithms.cpp calculations.cpp visualization.cpp history.cpp -o analyzer
./analyzer
```

## How to use

1. Choose `1` for manual requests or `2` for randomly generated requests.
2. Enter the disk size and initial head position.
3. Enter requests (manual mode) or the desired random request count.
4. Choose the initial direction for SCAN, C-SCAN, and LOOK.
5. Review detailed results and the performance dashboard.
6. Choose an algorithm to view its movement path.
7. Save the analysis if you want it recorded in `history.txt`.
8. Choose menu option `3` later to view saved history.

## Example manual test

- Cylinders: `200` (valid positions: 0 through 199)
- Initial head: `50`
- Requests: `82, 170, 43, 140, 24, 16, 190`
- Direction: `2` (Right)

## Notes about the simulation

- SCAN travels to the physical disk boundary before reversing.
- C-SCAN travels to the boundary, wraps to the opposite boundary, then continues in the same direction. The wrap movement is included in total movement.
- LOOK reverses at the last pending request rather than travelling to the physical boundary.
- SSTF chooses the nearest pending request; ties are resolved by the first matching request in the remaining input order.
- Lowest total head movement is a simplified performance measure, not a complete model of real disk latency.
- This is a simulator; it does not access or control your physical hard drive.
