#include "ScoreboardEntry.h"

#include <stdexcept>
#include <algorithm>

namespace Model
{
ScoreboardEntry::ScoreboardEntry(string playerName, int puzzleNumber, int completionTime)
{
    if (playerName == "")
    {
        throw invalid_argument("playerName cannot be blank.");
    }
    if (puzzleNumber < 0)
    {
        throw invalid_argument("puzzleNumber cannot be < 0");
    }
    if (completionTime < 0)
    {
        throw invalid_argument("completionTime cannot be < 0");
    }
    this->playerName = playerName;
    this->puzzleNumber = puzzleNumber;
    this->completionTime = completionTime;
}

ScoreboardEntry::~ScoreboardEntry() {}

string ScoreboardEntry::getPlayerName() const
{
    return this->playerName;
}

int ScoreboardEntry::getPuzzleNumber() const
{
    return this->puzzleNumber;
}

int ScoreboardEntry::getCompletionTime() const
{
    return this->completionTime;
}

bool ScoreboardEntry::operator==(const ScoreboardEntry& other) const
{
    return (this->completionTime == other.getCompletionTime()
            && this->puzzleNumber == other.getPuzzleNumber()
            && this->playerName == other.getPlayerName());
}

bool ScoreboardEntry::compareByCompletionTimeComparator(const ScoreboardEntry& original, const ScoreboardEntry& other)
{
    return (original.getCompletionTime() < other.getCompletionTime());
}

bool ScoreboardEntry::compareByPuzzleNumberComparator(const ScoreboardEntry& original, const ScoreboardEntry& other)
{
    if (original.getPuzzleNumber() == other.getPuzzleNumber())
    {
        return ScoreboardEntry::compareByCompletionTimeComparator(original, other);
    }
    return (original.getPuzzleNumber() > other.getPuzzleNumber());
}

}
