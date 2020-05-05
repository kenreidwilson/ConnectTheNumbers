#include "PuzzleParser.h"

#include <sstream>

#include "FileIOUtility.h"
using namespace Utility;

namespace Model
{
const string PuzzleParser::puzzlesFilePath = "puzzles.csv";
const string PuzzleParser::userSavedPuzzlesFilePath = "user_puzzles.csv";

PuzzleParser::PuzzleParser() {}

PuzzleParser::~PuzzleParser() {}

PuzzleManager* PuzzleParser::loadOriginalPuzzle(int puzzleNumber)
{
    return parsePuzzle(this->puzzlesFilePath, puzzleNumber);
}

PuzzleManager* PuzzleParser::loadUserPuzzle(int puzzleNumber)
{
    return parsePuzzle(this->userSavedPuzzlesFilePath, puzzleNumber);
}

void PuzzleParser::saveUserPuzzle(PuzzleManager* puzzle, int puzzleNumber)
{
    try
    {
        FileIOUtility::writeLine(this->userSavedPuzzlesFilePath, serializePuzzle(puzzle), puzzleNumber);
    }
    catch (invalid_argument)
    {
        FileIOUtility::writeLines(this->userSavedPuzzlesFilePath, FileIOUtility::readLines(this->puzzlesFilePath));
        FileIOUtility::writeLine(this->userSavedPuzzlesFilePath, serializePuzzle(puzzle), puzzleNumber);
    }
}

PuzzleManager* PuzzleParser::parsePuzzle(string fileName, int puzzleNumber)
{
    string puzzleString = FileIOUtility::readLine(fileName, puzzleNumber);
    PuzzleManager* puzzle = new PuzzleManager();

    string currentSquare = "";
    for (char& currentChar : puzzleString)
    {
        if (currentChar == this->csvDelimiter)
        {
            addSquareToPuzzle(*puzzle, currentSquare);
            currentSquare = "";
        }
        else
        {
            currentSquare += currentChar;
        }
    }
    addSquareToPuzzle(*puzzle, currentSquare);

    return puzzle;
}

void PuzzleParser::addSquareToPuzzle(PuzzleManager &puzzle, string squareRepresentation)
{
    char delimiter;
    bool hasPassedDelimiter = false;
    string squarePositionString = "";
    string squareValueString = "";

    for (char& currentChar : squareRepresentation)
    {
        if (!hasPassedDelimiter)
        {
            if (currentChar == this->userDefinedValueIdentifier || currentChar == this->puzzleDefinedValueIdentifier)
            {
                delimiter = currentChar;
                hasPassedDelimiter = true;
            }
            else
            {
                squarePositionString += currentChar;
            }
        }
        else
        {
            squareValueString +=  currentChar;
        }
    }

    int squarePosition;
    int squareValue;
    try
    {
        squarePosition = stoi(squarePositionString);
        squareValue = stoi(squareValueString);
    }
    catch (invalid_argument)
    {
        return;
    }

    int squareXCoordinate = puzzle.getXCoordinateFromPosition(squarePosition);
    int squareYCoordinate = puzzle.getYCoordinateFromPosition(squarePosition);

    puzzle.setSquareValue(squareXCoordinate, squareYCoordinate, squareValue);
    if (delimiter == this->puzzleDefinedValueIdentifier)
    {
        puzzle.addPuzzleDefinedPosition(squareXCoordinate, squareYCoordinate);
    }
}

string PuzzleParser::serializePuzzle(PuzzleManager* puzzle)
{
    stringstream puzzleStringStream;
    for (int y = 0; y < puzzle->height; y++)
    {
        for (int x = 0; x < puzzle->width; x++)
        {
            char delimiter = puzzle->isPuzzleDefinedPosition(x, y) ? this->puzzleDefinedValueIdentifier : this->userDefinedValueIdentifier;
            puzzleStringStream << (y * puzzle->height + x) << delimiter << puzzle->getSquareValue(x, y);
            if (x != puzzle->width - 1 || y != puzzle->height - 1)
            {
                puzzleStringStream << this->csvDelimiter;
            }
        }
    }
    return puzzleStringStream.str();
}
}
