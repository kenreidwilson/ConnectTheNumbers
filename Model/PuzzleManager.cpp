#include "PuzzleManager.h"

#include <stdexcept>
#include <algorithm>

namespace Model
{
PuzzleManager::PuzzleManager() {}

PuzzleManager::~PuzzleManager() {}

int PuzzleManager::getSquareValue(int x, int y) const
{
    if (x >= this->width || x < 0 || y >= this->height || y < 0)
    {
        return -1;
    }
    return this->gameBoard[y][x];
}

void PuzzleManager::setSquareValue(int x, int y, int value)
{
    if (x >= this->width)
    {
        throw invalid_argument("x is greater than the width of the puzzle.");
    }
    if (x < 0)
    {
        throw invalid_argument("x is less than 0.");
    }
    if (y >= this->height)
    {
        throw invalid_argument("y is greater than the height of the puzzle.");
    }
    if (y < 0)
    {
        throw invalid_argument("y is less than 0.");
    }
    if (isPuzzleDefinedPosition(x, y))
    {
        throw invalid_argument("that position is a puzzle defined position.");
    }
    this->gameBoard[y][x] = value;
}

void PuzzleManager::addPuzzleDefinedPosition(int x, int y)
{
    if (isPuzzleDefinedPosition(x, y))
    {
        return;
    }
    this->puzzleDefinedSquares.push_back(getPositionFromCoordinates(x, y));
}

bool PuzzleManager::isPuzzleDefinedPosition(int x, int y)
{
    return count(this->puzzleDefinedSquares.begin(), this->puzzleDefinedSquares.end(), getPositionFromCoordinates(x, y));
}

int PuzzleManager::findSquarePositionWithValue(int value) const
{
    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            if (this->getSquareValue(x, y) == value)
            {
                return getPositionFromCoordinates(x, y);
            }
        }
    }
    return -1;
}

map<int, int> PuzzleManager::getNeighbors(int x, int y) const
{
    map<int, int> neighbors;

    int rightNeighborPosition = getPositionFromCoordinates(x + 1, y);
    int leftNeighborPosition  = getPositionFromCoordinates(x - 1, y);
    int aboveNeighborPosition = getPositionFromCoordinates(x, y + 1);
    int belowNeighborPosition = getPositionFromCoordinates(x, y - 1);

    neighbors[getSquareValue(getXCoordinateFromPosition(rightNeighborPosition), getYCoordinateFromPosition(rightNeighborPosition))] = rightNeighborPosition;
    neighbors[getSquareValue(getXCoordinateFromPosition(leftNeighborPosition), getYCoordinateFromPosition(leftNeighborPosition))] = leftNeighborPosition;
    neighbors[getSquareValue(getXCoordinateFromPosition(aboveNeighborPosition), getYCoordinateFromPosition(aboveNeighborPosition))] = aboveNeighborPosition;
    neighbors[getSquareValue(getXCoordinateFromPosition(belowNeighborPosition), getYCoordinateFromPosition(belowNeighborPosition))] = belowNeighborPosition;

    return neighbors;
}

bool PuzzleManager::evaluateGameBoard() const
{

    int currentSquarePosition = this->findSquarePositionWithValue(this->startSquareValue);
    if (getSquareValue(this->getXCoordinateFromPosition(currentSquarePosition), this->getYCoordinateFromPosition(currentSquarePosition)) == -1)
    {
        return false;
    }

    map<int, int> currentSquareNeighbors = this->getNeighbors(this->getXCoordinateFromPosition(currentSquarePosition), this->getYCoordinateFromPosition(currentSquarePosition));

    int currentValue = this->startSquareValue;

    while(currentValue != this->height * this->width && this->doNeighborsContainValue(currentSquareNeighbors, currentValue + 1))
    {
        currentValue += 1;
        currentSquarePosition = currentSquareNeighbors[currentValue];
        currentSquareNeighbors = this->getNeighbors(this->getXCoordinateFromPosition(currentSquarePosition), this->getYCoordinateFromPosition(currentSquarePosition));
    }
    return currentValue == (this->height * this->width);
}

bool PuzzleManager::doNeighborsContainValue(map<int, int> neighbors, int value) const
{
    map<int, int>::iterator neighborsIterator;
    neighborsIterator = neighbors.find(value);
    return neighborsIterator != neighbors.end();
}

int PuzzleManager::getPositionFromCoordinates(int x, int y) const
{
    if (x > this->width - 1 || y > this->height - 1)
    {
        return -1;
    }
    return y * this->height + x;
}

int PuzzleManager::getXCoordinateFromPosition(int position) const
{
    if (position > this->width * this->height)
    {
        return -1;
    }
    return position % this->width;
}

int PuzzleManager::getYCoordinateFromPosition(int position) const
{
    if (position > this->width * this->height)
    {
        return -1;
    }
    return position / this->height;
}
}
