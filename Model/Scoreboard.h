#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <vector>
using namespace std;

#include "ScoreboardEntry.h"

namespace Model
{
/**
* Tracks and persists scores for a game of Connect the Numbers.
*/
class Scoreboard
{
public:
    /**
    * Constructs a Scoreboard object.
    */
    Scoreboard();

    /**
    * Destructs a Scoreboard object.
    */
    virtual ~Scoreboard();

    /**
    * Adds a score to the scores and persists them.
    *
    * @throw invalid_argument if playerName is blank or puzzle number < 0 or completionTime < 0.
    *
    * @param playerName the name of the player who completed the puzzle.
    * @param puzzleNumber the puzzle number that was completed.
    * @param completionTime the time that the puzzle was completed in seconds.
    */
    void addScore(string playerName, int puzzleNumber, int completionTime);

    /**
    * Returns a vector of the top 10 scores.
    *
    * @postcondition scores will be sorted.
    *
    * @param numberOfScores the number of scores you want returned
    *           if numberOfScores > scores.size() then all scores are returned.
    * @param comparator the comparision function that will compare ScoreboardEntries.
    *
    * @return a vector of the top 10 scores
    */
    vector<ScoreboardEntry> getTopScores(int numberOfScores, bool (*comparator)(const ScoreboardEntry& original, const ScoreboardEntry& other));

    /**
    * Clears all scores and clears persisted scores.
    *
    * @postcondition scores.size() == 0
    */
    void reset();
private:
    const static char scoreboardEntryDelimiter = ',';

    /**
    * The file path to "the CSV file" that persists score entries.
    */
    string scoreboardFilePath;

    /**
    * A vector containing all scores.
    */
    vector<ScoreboardEntry> scores;

    /**
    * Populates scores from "the CSV file".
    *
    * @postcondition current scores will be replaced.
    */
    void parseScores();

    /**
    * Returns a ScoreboardEntry that is parsed from the string provided.
    *
    * @throw invalid_argument if score cannot be parsed.
    *
    * @param scoreboardEntryRepresentation the string respresenting a ScoreboardEntry
    *
    * @return a ScoreboardEntry that is parsed from the string provided.
    */
    ScoreboardEntry parseScore(string &scoreboardEntryRepresentation);

    /**
    * Persists scores to "the CSV file".
    */
    void writeScores() const;

    /**
    * Returns a string representation of a ScoreboardEntry.
    *
    * @param score the ScoreboardEntry that will be serialized.
    *
    * @return a string representation of a ScoreboardEntry.
    */
    string serializeScoreboardEntry(ScoreboardEntry score) const;
};
}

#endif // SCOREBOARD_H
