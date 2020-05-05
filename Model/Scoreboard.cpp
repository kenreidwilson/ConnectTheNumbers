#include "Scoreboard.h"

#include <algorithm>
#include <sstream>

#include "FileIOUtility.h"
using namespace Utility;

namespace Model
{
Scoreboard::Scoreboard()
{
    this->scoreboardFilePath = "scoreboard.csv";
    try
    {
        this->parseScores();
    }
    catch (invalid_argument)
    {
        FileIOUtility::initializeFile(this->scoreboardFilePath);
    }
}

Scoreboard::~Scoreboard() {}

void Scoreboard::addScore(string playerName, int puzzleNumber, int completionTime)
{
    this->scores.push_back(ScoreboardEntry(playerName, puzzleNumber, completionTime));
    writeScores();
}

vector<ScoreboardEntry> Scoreboard::getTopScores(int numberOfScores, bool (*comparator)(const ScoreboardEntry& original, const ScoreboardEntry& other))
{
    sort(this->scores.begin(), this->scores.end(), comparator);
    if (this->scores.size() <= numberOfScores)
    {
        return this->scores;
    }
    vector<ScoreboardEntry> topScores;
    topScores.reserve(numberOfScores);
    for (int i = 0; i <= numberOfScores; i++)
    {
        topScores.push_back(this->scores[i]);
    }
    return topScores;
}

void Scoreboard::reset()
{
    this->scores.clear();
    writeScores();
}

void Scoreboard::parseScores()
{
    vector<string> scoreStrings = FileIOUtility::readLines(this->scoreboardFilePath);
    this->scores.reserve(scoreStrings.size());
    for (string score : FileIOUtility::readLines(this->scoreboardFilePath))
    {
        try
        {
            this->scores.push_back(parseScore(score));
        }
        catch (invalid_argument e)
        {
            continue;
        }

    }
}

ScoreboardEntry Scoreboard::parseScore(string &scoreboardEntryRepresentation)
{
    string playerName;
    string puzzleNumberString;
    string completionTimeString;

    int delimitersPassed = 0;
    for (char& currentChar : scoreboardEntryRepresentation)
    {
        if (currentChar == this->scoreboardEntryDelimiter)
        {
            delimitersPassed++;
        }
        else if (delimitersPassed == 0)
        {
            playerName += currentChar;
        }
        else if (delimitersPassed == 1)
        {
            puzzleNumberString += currentChar;
        }
        else if (delimitersPassed == 2)
        {
            completionTimeString += currentChar;
        }
    }
    return ScoreboardEntry(playerName, stoi(puzzleNumberString), stoi(completionTimeString));
}

void Scoreboard::writeScores() const
{
    vector<string> scoreSerializations;
    for (ScoreboardEntry score : this->scores)
    {
        scoreSerializations.push_back(serializeScoreboardEntry(score));
    }
    FileIOUtility::writeLines(this->scoreboardFilePath, scoreSerializations);
}

string Scoreboard::serializeScoreboardEntry(ScoreboardEntry score) const
{
    stringstream scoreSerialization;
    scoreSerialization << score.getPlayerName() << this->scoreboardEntryDelimiter;
    scoreSerialization << score.getPuzzleNumber() << this->scoreboardEntryDelimiter;
    scoreSerialization << score.getCompletionTime();
    return scoreSerialization.str();
}
}
