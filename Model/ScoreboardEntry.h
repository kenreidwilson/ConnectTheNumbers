#ifndef SCOREBOARDENTRY_H
#define SCOREBOARDENTRY_H

#include <string>
using namespace std;

namespace Model
{
class ScoreboardEntry
{
public:
    /**
    * Constructs a ScoreboardEntry object.
    *
    * @throw invalid_argument if playerName is blank or puzzle number < 0 or completionTime < 0.
    *
    * @param playerName the name of the player who completed the puzzle.
    * @param puzzleNumber the puzzle number that was completed.
    * @param completionTime the time that the puzzle was completed in seconds.
    */
    ScoreboardEntry(string playerName, int puzzleNumber, int completionTime);

    /**
    * Destructs a ScoreboardEntry object.
    */
    virtual ~ScoreboardEntry();

    /**
    * Returns the entry's playerName.
    *
    * @return the entry's playerName.
    */
    string getPlayerName() const;

    /**
    * Returns the entry's puzzleNumber.
    *
    * @return the entry's puzzleNumber.
    */
    int getPuzzleNumber() const;

    /**
    * Returns the entry's completionTime.
    *
    * @return the entry's completionTime.
    */
    int getCompletionTime() const;

    /**
    * Provides the == operator.
    */
    bool operator==(const ScoreboardEntry& other) const;

    /**
    * Compares the ScoreboardEntries by their completionTime.
    */
    static bool compareByCompletionTimeComparator(const ScoreboardEntry& original, const ScoreboardEntry& other);

    /**
    * Compares the ScoreboardEntries by their puzzleNumber then their completionTime.
    */
    static bool compareByPuzzleNumberComparator(const ScoreboardEntry& original, const ScoreboardEntry& other);

private:
    /**
    * Stores the entry's playerName.
    */
    string playerName;

    /**
    * Stores the entry's puzzleNumber.
    */
    int puzzleNumber;

    /**
    * Stores the entry's completionTime.
    */
    int completionTime;
};
}

#endif // SCOREBOARDENTRY_H
