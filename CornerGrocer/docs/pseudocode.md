# CornerGrocer Tracker Pseudocode

PROGRAM CornerGrocerTracker

CREATE GroceryTracker object named tracker
CALL tracker.LoadItemsFromFile("CornerGrocerInput.txt")
CALL tracker.WriteBackupFile("frequency.dat")

REPEAT
  DISPLAY menu options 1-4
  READ user menu choice

  IF choice == 1 THEN
     PROMPT user for item name
     READ item name
     count = CALL tracker.GetItemFrequency(item name)
     DISPLAY item name and count
  ELSE IF choice == 2 THEN
     CALL tracker.PrintAllFrequencies()
  ELSE IF choice == 3 THEN
     CALL tracker.PrintHistogram()
  ELSE IF choice == 4 THEN
     DISPLAY exit message
  ELSE
     DISPLAY "Invalid option"
  ENDIF

UNTIL choice == 4

END PROGRAM
