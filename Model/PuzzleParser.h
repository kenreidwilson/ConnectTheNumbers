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
    void saveUserPuzzle(PuzzleManager& puzzle, int puzzleNumber);

private:
    const static string puzzlesFilePath;
    const static string userSavedPuzzlesFilePath;
    const static char csvDelimiter = ',';
    const static char userDefinedValueIdentifier = '-';
    const static char puzzleDefinedValueIdentifier = ':';

    PuzzleManager* parsePuzzle(string filePath, int puzzleNumber);
    void addSquareToPuzzle(PuzzleManager& puzzle, string& squareRepresentation);
    string serializePuzzle(PuzzleManager& puzzle);
};
}

#endif // PUZZLEPARSER_H
