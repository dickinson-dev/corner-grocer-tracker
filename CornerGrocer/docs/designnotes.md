# Design Notes (Corner Grocer Tracker)

## Key goals

- Keep `main.cpp` small and focused on user interaction.
- Put data + business logic into a single class (`GroceryTracker`).
- Use simple, readable C++ with clear naming and comments.

## Data handling choices

- Input file is processed line-by-line (`std::getline`) because each purchase record is stored on its own line.
- Items are normalized (trim + lowercase) before inserting into the map.
  - This makes counting reliable even if capitalization varies (e.g., "Apple" vs "apple").

## Data structure

- `std::map<std::string, int>` chosen for:
  - fast lookups for Option 1
  - automatic alphabetical ordering for Option 2 output
  - simple iteration for histogram output

## Backup file policy

- `frequency.dat` is written automatically at program start.
- Format: `item count` per line.
- Purpose: preserves a snapshot of daily totals without requiring a menu option.

## Input validation

- Menu input is validated to handle:
  - non-numeric input (e.g., "abc")
  - out-of-range values (e.g., 9)
- Item search includes a minimal suggestion feature:
  - checks singular/plural by adding/removing trailing `s`
  - avoids aggressive guessing to prevent incorrect matches

## Testing checklist

- Option 1 returns correct counts and suggests plural/singular when applicable.
- Option 2 prints all items with counts.
- Option 3 prints histogram where symbol count matches frequency.
- `frequency.dat` is created and matches the map contents.
