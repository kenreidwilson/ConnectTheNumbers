#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>

#include "Scoreboard.h"
#include "UserSettings.h"
using namespace Model;

namespace View
{
/**
* A window that allows the user to navigate to all puzzles, check the scoreboard, and edit their settings.
*/
class GameMainWindow : public Fl_Window
{
public:
    /**
    * Constructs a GameMainWindow.
    */
    GameMainWindow(int width, int height, const char* title);

    /**
    * Destructs a GameMainWindow.
    */
    virtual ~GameMainWindow();

private:
    const int numberOfPuzzles = 12;
    map<Fl_Button*, int*> buttonNumberMap;
    vector<string*> buttonLabels;

    Fl_Output* gameTitleLabel;
    Fl_Button* scoreboardButton;
    Fl_Button* setColorButton;
    UserSettings* userSettings;
    Scoreboard* scoreboard;

    void initializePuzzleButtons();
    static void cbOpenPuzzle(Fl_Widget* widget, void* data);
    static void cbShowScoreBoard(Fl_Widget* widget, void* data);
    static void cbSetUserColorPreference(Fl_Widget* widget, void* data);
    void handlePlayerWin(Fl_Button* senderButton, int timerTime);
    string getPlayerName();
};
}
#endif // GAMEMAINWINDOW_H
