#include "GroceryTracker.h"

#include <iostream>  // std::cout, std::cin
#include <limits>    // std::numeric_limits
#include <string>    // std::string

/*
 * printMenu
 * ---------
 * Displays the required menu options to the user.
 */
static void printMenu() {
    std::cout << "\n==== Corner Grocer Item Tracker ====\n";
    std::cout << "1) Look up an item frequency\n";
    std::cout << "2) Print all item frequencies\n";
    std::cout << "3) Print histogram\n";
    std::cout << "4) Exit\n";
    std::cout << "Select an option (1-4): ";
}

/*
 * readMenuChoice
 * --------------
 * Validates user input for menu selection.
 * Ensures the program does not crash on non-numeric input.
 */
static int readMenuChoice() {
    int choice = 0;

    while (true) {
        if (std::cin >> choice && choice >= 1 && choice <= 4) {
            // Remove leftover characters on the same line (including newline)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        // Input failed (non-numeric) or out of range
        std::cout << "Invalid input. Enter a number 1-4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    GroceryTracker tracker;

    // NOTE: This assumes the program runs with cwd set to the /data folder.
    // If cwd is different, adjust the path or move the input file accordingly.
    const std::string inputFile = "CornerGrocerInput.txt";
    const std::string backupFile = "frequency.dat";

    // Load input purchase data from file
    if (!tracker.loadItemsFromFile(inputFile)) {
        std::cout << "Program cannot continue without input data.\n";
        return 1;
    }

    // Create backup file automatically on startup (no user intervention)
    tracker.writeBackupFile(backupFile);

    int choice = 0;
    while (choice != 4) {
        printMenu();
        choice = readMenuChoice();

        if (choice == 1) {
            std::string item;
            std::cout << "Enter item name: ";
            std::getline(std::cin, item);

            const int count = tracker.getItemFrequency(item);

            // If found, print frequency; otherwise offer suggestion(s)
            if (count > 0) {
                std::cout << item << " was purchased " << count << " time(s).\n";
            } else {
                std::cout << "No exact match for '" << item << "'.\n";

                const auto suggestions = tracker.suggestItems(item);
                if (!suggestions.empty()) {
                    std::cout << "Did you mean:\n";
                    for (const auto& s : suggestions) {
                        std::cout << "  - " << s << " (" << tracker.getItemFrequency(s) << ")\n";
                    }
                }
            }
        }
        else if (choice == 2) {
            tracker.printAllFrequencies();
        }
        else if (choice == 3) {
            tracker.printHistogram('*');
        }
        else if (choice == 4) {
            std::cout << "Goodbye.\n";
        }
    }

    return 0;
}