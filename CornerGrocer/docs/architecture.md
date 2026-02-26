# Architecture (Corner Grocer Tracker)

## Overview

The program is a console-based C++ application that reads a daily purchase log, counts item frequency, provides menu-driven queries/reports, and writes a backup data file.

## Components

### 1) main.cpp (UI / Control Flow)

Responsibilities:

- display menu
- validate menu selection
- collect user input for item search
- call methods on `GroceryTracker`

Does NOT:

- parse files
- manage data structures
- perform counting logic

### 2) GroceryTracker (Business Logic)

Responsibilities:

- read input file and build frequency map
- provide lookup for single item frequency
- provide full frequency report
- provide histogram report
- write backup file

## Data Flow

1. Program starts
2. `loadItemsFromFile()` reads input purchase log
3. `writeBackupFile()` creates `frequency.dat`
4. User selects menu options:
   - Option 1: lookup in map (+ suggestion)
   - Option 2: iterate map and print counts
   - Option 3: iterate map and print histogram
   - Option 4: exit

## Data Structures

- `std::map<std::string, int> m_itemCounts`
  - Key: normalized item name
  - Value: purchase frequency

## Reliability features

- File open checks for both input and output
- Menu input validation prevents crashes on bad input
- Normalization ensures consistent counting
