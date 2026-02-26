# Corner Grocer Grocery Tracker

## Summary

This program reads a daily purchase log (`CornerGrocerInput.txt`), counts how many times each item appears, and provides a menu interface to:

1. Look up the frequency of a specific item
2. Print all item frequencies
3. Print a histogram representation of frequencies
4. Exit

The program also creates a backup file (`frequency.dat`) automatically at startup.

## How to Run

### Assumed project layout

- `src/` contains:
  - `main.cpp`
  - `GroceryTracker.cpp`
  - `GroceryTracker.h`
- `data/` contains:
  - `CornerGrocerInput.txt`

### Run behavior / working directory

This project is configured to run with the working directory set to `data/`,
so the input file can be referenced by name:

- `CornerGrocerInput.txt`

Output files created:

- `frequency.dat` (written into the working directory)

## Menu Options

- **Option 1:** Search for an item and print its frequency.
  - If an exact match is not found, the program suggests close matches
    using a simple plural/singular rule (add/remove trailing `s`).
- **Option 2:** Print all items and their frequencies.
- **Option 3:** Print histogram using `*` for each counted purchase.
- **Option 4:** Exit.

## Build Notes (MSVC / Visual Studio)

This project builds with Microsoft Visual C++ (MSVC). Ensure you have:

- Visual Studio 2022 (Desktop development with C++)
or run VS Code from the Visual Studio Developer Command Prompt.

## Files

- `src/main.cpp` - Menu UI and input validation
- `src/GroceryTracker.h/.cpp` - File parsing, frequency tracking, reports
- `data/CornerGrocerInput.txt` - Input purchase log
- `data/frequency.dat` - Output backup frequency file

