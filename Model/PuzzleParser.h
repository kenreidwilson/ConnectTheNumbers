#ifndef PUZZLEPARSER_H
#define PUZZLEPARSER_H

#include <tuple>
#include <string>
using namespace std;

#include "PuzzleManager.h"

namespace Model
{
/**
* Handles reading and writing Connect the Numbers Puzzles to a CSV file.
*/
class PuzzleParser
{
public:
    /**
    * Constructs a new PuzzleParser object.
    */
    PuzzleParser();

    /**
    * Deconstructs a PuzzleManager object.
    */
    virtual ~PuzzleParser();

    /**
    * Loads a puzzle from the puzzles CSV file.
    *
    * @param puzzleNumber the puzzle's number.
    *
    * @return a puzzle parsed from the puzzles CSV file.
    */
    PuzzleManager* loadOriginalPuzzle(int puzzleNumber);

    /**
    * Loads a puzzle from the userSavedPuzzles CSV file.
    *
    * @param puzzleNumber the puzzle's number.
    *
    * @return a puzzle parsed from the userSavedPuzzles CSV file.
    */
    PuzzleManager* loadUserPuzzle(int puzzleNumber);

    /**
    * Saves the user's progress in a puzzle to the userSavedPuzzles file.
    * If the user puzzles file doesn't exist it is created using the puzzles file.
    *
    * @param puzzle the puzzle to be saved.
    * @param puzzleNumber the line to save the puzzle on.
    */
    void saveUserPuzzle(PuzzleManager* puzzle, int puzzleNumber);

private:
    /**
    * The filepath of the CSV file that saves puzzles.
    */
    const static string puzzlesFilePath;

    /**
    * The filepath of the CSV file that saves a user's progress through a puzzle.
    */
    const static string userSavedPuzzlesFilePath;

    /**
    * The delimiter that divides squares in the CSV files.
    */
    const static char csvDelimiter = ',';

    /**
    * The delimiter that divides positions and user defined values.
    */
    const static char userDefinedValueIdentifier = '-';

    /**
    * The delimiter that divides positions and puzzle defined values.
    */
    const static char puzzleDefinedValueIdentifier = ':';

    /**
    * Parses a puzzle from a CSV file that is on the same line as the puzzleNumber parameter.
    *
    * @param filePath the path to the csv file to parse from.
    * @param puzzleNumber the line to parse the puzzle from.
    *
    * @return The puzzle's PuzzleManager.
    */
    PuzzleManager* parsePuzzle(string filePath, int puzzleNumber);

    /**
    * Parses the square representation and adds it to the provided puzzle.
    *
    * @param puzzle the puzzle that the square will be added to.
    * @param squareRepresentation a string representation of a square.
    */
    void addSquareToPuzzle(PuzzleManager* puzzle, string& squareRepresentation);

    /**
    * Returns a parsable string represention of a PuzzleManager object.
    *
    * @param puzzle a reference to the puzzle object that is being serialized.
    *
    * @return a parsable string represention of a PuzzleManager object.
    */
    string serializePuzzle(PuzzleManager* puzzle);
};
}

#endif // PUZZLEPARSER_H
