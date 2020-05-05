#ifndef PUZZLEMANAGER_H
#define PUZZLEMANAGER_H

#include <map>
#include <vector>
using namespace std;

namespace Model
{
/**
* Tracks the state of a Connect the Numbers Puzzle and can determine when the puzzle is solved or not.
*/
class PuzzleManager
{
public:
    /**
    * Constructs a new PuzzleManager object.
    */
    PuzzleManager();

    /**
    * Deconstructs a PuzzleManager object.
    */
    virtual ~PuzzleManager();

    /**
    * Returns the value of a square at the provided X and Y.
    *
    * @param x the X coordinate of the square.
    * @param y the Y coordinate of the square.
    *
    * @return the value of the square and -1 if the square doesn't exist.
    */
    int getSquareValue(int x, int y) const;

    /**
    * Sets the value of a square at the provided X and Y.
    *
    * @param x the X coordinate of the square.
    * @param y the Y coordinate of the square.
    * @param value the value of the square.
    *
    * @throw invalid_argument if x >= this->width || this->width < 0 || y >= this->height || y < 0
    *           or if the position is a puzzle defined position.
    */
    void setSquareValue(int x, int y, int value);

    /**
    * Makes the square at the provided coordinates immutable for the player.
    *
    * @param x the X coordinate of the square.
    * @param y the Y coordinate of the square.
    */
    void addPuzzleDefinedPosition(int x, int y);

    /**
    * Returns true if the provided X and Y coordinates are a puzzle defined square.
    *
    * @param x the X coordinate of the square.
    * @param y the Y coordinate of the square.
    *
    * @return true if the square is a puzzle defined square, false otherwise.
    */
    bool isPuzzleDefinedPosition(int x, int y);

    /**
    * Evalutes the game board and returns true if it is solved.
    *
    * @return true if the game board state is solved, false otherwise.
    */
    bool evaluateGameBoard() const;

    /**
    * Returns the position of a square from the X and Y provided,
    *   and -1 if the X or Y is out of bounds.
    *
    * @param x the X coordinate of the square.
    * @param y the Y coordinate of the square.
    *
    * @return the position of a square in a linear structure.
    */
    int getPositionFromCoordinates(int x, int y) const;

    /**
    * Returns the X coordinate from a square position in a linear structure.
    *   and -1 if the position is out of bounds.
    *
    * @param position the position of a square in a linear structure.
    *
    * @return the X coordinate of the square.
    */
    int getXCoordinateFromPosition(int position) const;

    /**
    * Returns the Y coordinate from a square position in a linear structure,
    *   and -1 if the position is out of bounds.
    *
    * @param position the position of a square in a linear structure.
    *
    * @return the Y coordinate of the square.
    */
    int getYCoordinateFromPosition(int position) const;

    /**
    * The height of the puzzle board.
    */
    const static int height = 8;

    /**
    * The width of the puzzle board.
    */
    const static int width = 8;

private:
    /**
    * The starting value of the puzzle.
    */
    const static int startSquareValue = 1;

    /**
    * A 2D array that tracks the X and Y of squares on the board and the value contained within them.
    */
    int gameBoard[height][width] = {0};

    /**
    * A vector containing square positions that contain puzzle defined values.
    * The player will not be able to change these values.
    */
    vector<int> puzzleDefinedSquares;

    /**
    * Returns the position of the first square, in a linear structure, that contains the
    *   provided value.
    *
    * @param value the value of the square being searched for.
    *
    * @return the position of the first square containing the value.
    */
    int findSquarePositionWithValue(int value) const;

    /**
    * Returns a map of neighbors of the provided square position.
    * The key to the map is the value of the neighbor, and the value is the position of the neighbor.
    * This will be used to evaluate the game board.
    *
    * @param x the X value of the square being queried.
    * @param y the Y value of the square being queried.
    *
    * @return a map with the key being the value of the neighboring square, and the value being
    *           the position of the neighboring square.
    */
    map<int, int> getNeighbors(int x, int y) const;

    /**
    * Returns true if the neighbor map contains the value provided.
    *
    * @param neighbors a map of squares where the key is the value of the square and the value being
    *           the position of the square.
    * @param value the value of a neighboring square being searched for.
    *
    * @return true if the neighbor map contains the value provided, false otherwise.
    */
    bool doNeighborsContainValue(map<int, int> neighbors, int value) const;
};
}
#endif // PUZZLEMANAGER_H
