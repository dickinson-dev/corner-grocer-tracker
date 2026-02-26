#ifndef GROCERY_TRACKER_H_
#define GROCERY_TRACKER_H_

#include <map>      // std::map for item -> frequency
#include <string>   // std::string
#include <vector>   // std::vector for suggestion list

/*
 * GroceryTracker
 * --------------
 * Responsibility:
 *  - Load item purchase data from a text file (one item per line)
 *  - Track item frequencies using a map
 *  - Provide query + reporting outputs (list + histogram)
 *  - Write a backup file (frequency.dat) automatically
 */

class GroceryTracker {
public:
    // Reads the input file and builds the frequency map.
    // Returns true if the file was opened/processed successfully.
    bool loadItemsFromFile(const std::string& t_inputPath);

    // Writes the backup data file (frequency.dat).
    // Returns true if the file was created/written successfully.
    bool writeBackupFile(const std::string& t_outputPath) const;

    // Returns the purchase count for a single item (case-insensitive).
    // If the item does not exist, returns 0.
    int getItemFrequency(const std::string& t_item) const;

    // Suggests close matches when an item isn't found.
    // Current rule: plural/singular check by adding/removing trailing 's'.
    std::vector<std::string> suggestItems(const std::string& t_item) const;

    // Prints every item and its frequency to the console.
    void printAllFrequencies() const;

    // Prints a text-based histogram using a symbol repeated by frequency.
    void printHistogram(char t_symbol = '*') const;

private:
    // Stores: normalized_item_name -> frequency
    std::map<std::string, int> m_itemCounts;

    // Normalizes input for consistent matching:
    //  - trims whitespace
    //  - lowercases text
    static std::string normalize(const std::string& t_text);
};

#endif  // GROCERY_TRACKER_H_