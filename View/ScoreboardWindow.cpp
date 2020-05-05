#include "ScoreboardWindow.h"

#include <sstream>
#include <iomanip>

namespace View
{
ScoreboardWindow::ScoreboardWindow(Scoreboard* scoreboard) : Fl_Window(700, 350, "Top 10 ScoreBoard")
{
    this->begin();
    this->scoreboard = scoreboard;

    this->scoreDisplay = new Fl_Text_Display(20, 30, 500, 250, "Top Scores");
    this->scoreDisplay->textfont(Fl_Font(4));
    this->scoreDisplayBuffer = new Fl_Text_Buffer();
    this->scoreDisplay->buffer(this->scoreDisplayBuffer);
    auto topScores = scoreboard->getTopScores(this->numberOfScores, ScoreboardEntry::compareByCompletionTimeComparator);
    this->scoreDisplayBuffer->text(this->formatScoreboardEntry(topScores).c_str());

    this->sortButtonsLabel = new Fl_Box(550, 50, 120,35, "Sort by:");
    this->displayScoresByFastestTimeButton = new Fl_Button(550, 80, 120, 35, "Fastest Time");
    this->displayScoresByFastestTimeButton->callback(displayScoresOrderedByCompletionTime, this);
    this->displayScoresByPuzzleNumberButton = new Fl_Button(550, 130, 120, 35, "Puzzle Number");
    this->displayScoresByPuzzleNumberButton->callback(displayScoresOrderedByPuzzleNumber, this);
    this->resetButton = new Fl_Button(550, 220, 120, 35, "Reset");
    this->resetButton->callback(cbReset, this);

    this->end();
    this->resizable(this);
}

ScoreboardWindow::~ScoreboardWindow()
{
    delete this->displayScoresByPuzzleNumberButton;
    delete this->displayScoresByFastestTimeButton;
    delete this->resetButton;
    delete this->scoreDisplayBuffer;
    delete this->scoreDisplay;
    delete this->sortButtonsLabel;
}

void ScoreboardWindow::displayScoresOrderedByCompletionTime(Fl_Widget* widget, void* data)
{
    ScoreboardWindow* window = (ScoreboardWindow*) data;
    auto topScores = window->scoreboard->getTopScores(window->numberOfScores, ScoreboardEntry::compareByCompletionTimeComparator);
    window->scoreDisplayBuffer->text(window->formatScoreboardEntry(topScores).c_str());
}

void ScoreboardWindow::displayScoresOrderedByPuzzleNumber(Fl_Widget* widget, void* data)
{
    ScoreboardWindow* window = (ScoreboardWindow*) data;
    auto topScores = window->scoreboard->getTopScores(window->numberOfScores, ScoreboardEntry::compareByPuzzleNumberComparator);
    window->scoreDisplayBuffer->text(window->formatScoreboardEntry(topScores).c_str());
}

void ScoreboardWindow::cbReset(Fl_Widget* widget, void* data)
{
    ScoreboardWindow* window = (ScoreboardWindow*) data;
    window->scoreboard->reset();
    window->scoreDisplayBuffer->text("");
}

string ScoreboardWindow::formatScoreboardEntry(vector<ScoreboardEntry> &entries)
{
    stringstream outStream;
    int seperatorWidth = 20;
    outStream << left << setw(seperatorWidth) << "Player Name";
    outStream << left << setw(seperatorWidth) << "Completion Time";
    outStream << left << setw(seperatorWidth) << "Puzzle Number" << endl;
    for (ScoreboardEntry entry : entries)
    {
        outStream << left << setw(seperatorWidth) << entry.getPlayerName();
        outStream << left << setw(seperatorWidth) << entry.getCompletionTime();
        outStream << left << setw(seperatorWidth) << entry.getPuzzleNumber() << endl;
    }
    return outStream.str();
}
}
