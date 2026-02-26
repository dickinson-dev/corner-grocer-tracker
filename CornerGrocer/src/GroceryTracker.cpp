#include "GroceryTracker.h"

#include <algorithm>  // std::find_if, std::transform
#include <cctype>     // std::isspace, std::tolower
#include <fstream>    // std::ifstream, std::ofstream
#include <iomanip>    // std::setw, std::left
#include <iostream>   // std::cout, std::cerr

/*
 * normalize
 * ---------
 * Converts raw strings (from file or user input) into a consistent key:
 *  - trims leading/trailing whitespace
 *  - converts to lowercase
 * This allows case-insensitive comparisons and avoids " Apples" vs "apples".
 */
std::string GroceryTracker::normalize(const std::string& t_text) {
    std::string result = t_text;

    // Trim leading/trailing whitespace
    auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), notSpace));
    result.erase(std::find_if(result.rbegin(), result.rend(), notSpace).base(), result.end());

    // Convert to lowercase
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    return result;
}

/*
 * loadItemsFromFile
 * -----------------
 * Reads the input file line-by-line. Each line is an item purchased.
 * We normalize the item name and increment its counter in the map.
 */
bool GroceryTracker::loadItemsFromFile(const std::string& t_inputPath) {
    std::ifstream inputFile(t_inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file: " << t_inputPath << "\n";
        return false;
    }

    // Clear any previous run data
    m_itemCounts.clear();

    std::string item;
    while (std::getline(inputFile, item)) {
        const std::string key = normalize(item);

        // Ignore empty lines after trimming
        if (!key.empty()) {
            ++m_itemCounts[key];
        }
    }

    return true;
}

/*
 * writeBackupFile
 * ---------------
 * Writes item frequencies to a backup file (frequency.dat) automatically.
 * Output format: item count
 */
bool GroceryTracker::writeBackupFile(const std::string& t_outputPath) const {
    std::ofstream outFile(t_outputPath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file: " << t_outputPath << "\n";
        return false;
    }

    for (const auto& pair : m_itemCounts) {
        outFile << pair.first << " " << pair.second << "\n";
    }

    return true;
}

/*
 * getItemFrequency
 * ----------------
 * Case-insensitive frequency lookup. Returns 0 if not found.
 */
int GroceryTracker::getItemFrequency(const std::string& t_item) const {
    const std::string key = normalize(t_item);
    auto it = m_itemCounts.find(key);
    return (it != m_itemCounts.end()) ? it->second : 0;
}

/*
 * suggestItems
 * ------------
 * Provides simple suggestions when an exact match isn't found.
 * Current rule: add/remove trailing 's' (apple <-> apples).
 * This avoids guessing too aggressively and keeps results trustworthy.
 */
std::vector<std::string> GroceryTracker::suggestItems(const std::string& t_item) const {
    std::vector<std::string> suggestions;
    const std::string key = normalize(t_item);

    // Suggest plural by adding 's'
    if (m_itemCounts.find(key + "s") != m_itemCounts.end()) {
        suggestions.push_back(key + "s");
    }

    // Suggest singular by removing trailing 's'
    if (!key.empty() && key.back() == 's') {
        std::string singular = key.substr(0, key.size() - 1);
        if (m_itemCounts.find(singular) != m_itemCounts.end()) {
            suggestions.push_back(singular);
        }
    }

    return suggestions;
}

/*
 * printAllFrequencies
 * -------------------
 * Prints every item and its count (map iterates in alphabetical order).
 */
void GroceryTracker::printAllFrequencies() const {
    for (const auto& pair : m_itemCounts) {
        std::cout << std::left << std::setw(15) << pair.first << " " << pair.second << "\n";
    }
}

/*
 * printHistogram
 * --------------
 * Prints each item followed by a repeated symbol equal to its frequency.
 */
void GroceryTracker::printHistogram(char t_symbol) const {
    for (const auto& pair : m_itemCounts) {
        std::cout << std::left << std::setw(15) << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << t_symbol;
        }
        std::cout << "\n";
    }
}