#ifndef PUZZLEBOARDWINDOW_H
#define PUZZLEBOARDWINDOW_H

#include <FL/Fl.H>
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Output.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/fl_draw.H>

#include <vector>
#include <string>
using namespace std;

#include "../Model/PuzzleManager.h"
#include "../Model/PuzzleParser.h"
#include "../Model/UserSettings.h"
using namespace Model;

#include "GetUserInputWindow.h"

namespace View
{
/**
* A window that allows the user to play a game of Connect the Numbers.
*/
class PuzzleBoardWindow: public Fl_Window
{
public:
    /**
    * Constructs a PuzzleBoardWindowObject.
    *
    * @param puzzleNumber the puzzle number that will be loaded into this window.
    * @param userSettings a pointer to the user's settings for this window.
    */
    PuzzleBoardWindow(int puzzleNumber, UserSettings* userSettings);

    /**
    * Destructs a PuzzleBoardWindowObject.
    */
    virtual ~PuzzleBoardWindow();

    /**
    * Enums describing the ending result of a PuzzleBoardWindow.
    */
    enum WindowResult {WIN, NONE};

    /**
    * Returns the result enum of the window.
    *
    * @return the result enum of the window.
    */
    PuzzleBoardWindow::WindowResult getWindowResult();

    /**
    * Returns the timer's current time.
    *
    * @return the timer's current time.
    */
    int getTimerTime();

    /**
    * Renders the window.
    */
    void draw();

private:
    const int blankSquareValue = 0;

    PuzzleBoardWindow::WindowResult windowResult;
    Fl_Box* puzzleNumberBox;
    Fl_Box* timerLabel;
    Fl_Input* puzzleNumberOutputTextDisplay;
    Fl_Button* evaluatePuzzleButton;
    Fl_Button* resetPuzzleButton;
    Fl_Button* saveButton;
    Fl_Button* loadButton;
    Fl_Button* pauseButton;
    Fl_Output* timerOutput;

    int puzzleNumber;
    string* puzzleNumberLabel;
    int timerTime;
    bool isPaused = false;
    PuzzleParser puzzleParser;
    PuzzleManager* puzzle;
    UserSettings* userSettings;
    map<Fl_Button*, int> buttonNumberMap;

    void colorPuzzleButton(Fl_Button* button);
    void initializePuzzleButtons();
    void showPuzzleButtonLabels();
    void hidePuzzleButtonLabels();
    void resetTimer();
    int getUsersAddNumberInput();

    static void cbAddNumber(Fl_Widget* widget, void* data);
    static void cbTimer(void *data);
    static void cbResetPuzzleboard(Fl_Widget* widget, void* data);
    static void cbLoadUserSave(Fl_Widget* widget, void* data);
    static void cbSaveUserPuzzle(Fl_Widget* widget, void* data);
    static void cbPauseGame(Fl_Widget* widget, void* data);
    static void cbEvaluatePuzzle(Fl_Widget* widget, void* data);
};

#endif // PUZZLEBOARDWINDOW_H

}
