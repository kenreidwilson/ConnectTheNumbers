#ifndef SCOREBOARDWINDOW_H
#define SCOREBOARDWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Box.H>

#include <vector>
#include <string>
using namespace std;

#include "Scoreboard.h"
#include "ScoreboardEntry.h"
using namespace Model;


namespace View
{
/**
* A window that displays scores of completed Connect the Numbers games.
*/
class ScoreboardWindow: public Fl_Window
{
public:
    /**
    * Constructs a ScoreboardWindow.
    *
    * @param scoreboard A pointer the Scoreboard objecting keeping the scores.
    */
    ScoreboardWindow(Scoreboard* scoreboard);

    /**
    * Desctructs a ScoreboardWindow.
    */
    virtual ~ScoreboardWindow();

private:
    const int numberOfScores = 10;

    Scoreboard* scoreboard;
    Fl_Text_Display* scoreDisplay;
    Fl_Text_Buffer* scoreDisplayBuffer;
    Fl_Box* sortButtonsLabel;
    Fl_Button* displayScoresByFastestTimeButton;
    Fl_Button* displayScoresByPuzzleNumberButton;
    Fl_Button* resetButton;

    static void cbReset(Fl_Widget* widget, void* data);
    static void cbCancel(Fl_Widget* widget, void* data);
    static void displayScoresOrderedByCompletionTime(Fl_Widget* widget, void* data);
    static void displayScoresOrderedByPuzzleNumber(Fl_Widget* widget, void* data);
    string formatScoreboardEntry(vector<ScoreboardEntry> &entries);
};

}

#endif // SCOREBOARDWINDOW_H
