#include "PuzzleboardWindow.h"

#include <iostream>

namespace View
{
PuzzleBoardWindow::PuzzleBoardWindow(int puzzleNumber, UserSettings* userSettings) : Fl_Window(700, 600, "Puzzleboard Window")
{
    this->begin();

    this->windowResult = WindowResult::NONE;

    this->userSettings = userSettings;
    this->puzzleNumber = puzzleNumber;
    this->puzzleParser = PuzzleParser();
    this->puzzle = this->puzzleParser.loadOriginalPuzzle(puzzleNumber);
    this->initializePuzzleButtons();
    this->showPuzzleButtonLabels();

    this->puzzleNumberLabel = new string(("Puzzle #" + to_string(puzzleNumber)));
    this->puzzleNumberBox = new Fl_Box(600, 0, 50,50, puzzleNumberLabel->c_str());
    this->timerLabel = new Fl_Box(600, 100, 50,50,"Timer");
    this->timerOutput = new Fl_Output(600, 135, 50, 40);
    this->resetPuzzleButton = new Fl_Button(580, 200, 100, 35, "Reset");
    this->resetPuzzleButton->callback(cbResetPuzzleboard, this);
    this->loadButton = new Fl_Button(580, 350, 100, 35, "Load");
    this->loadButton->callback(cbLoadUserSave, this);
    this->saveButton = new Fl_Button(580, 400, 100, 35, "Save");
    this->saveButton->callback(cbSaveUserPuzzle, this);
    this->pauseButton = new Fl_Button(580, 500, 100, 35, "Pause");
    this->pauseButton->callback(cbPauseGame, this);
    this->evaluatePuzzleButton = new Fl_Button(580, 250, 100, 35, "Evaluate");
    this->evaluatePuzzleButton->callback(cbEvaluatePuzzle, this);

    this->timerTime = 0;
    Fl::add_timeout(1, cbTimer, this);

    this->end();
    this->resizable(this);
}

void PuzzleBoardWindow:: draw()
{
    Fl_Window::draw();
}

void PuzzleBoardWindow::initializePuzzleButtons()
{
    const int ENDPOINT = 544;
    const int BOXLENGTH = 65;
    const int STARTPOINT = 25;
    const int BUTTONLENGTH = 55;

    int current = 0;
    int amount = 0;

    for (int i = 0; i < this->puzzle->width * this->puzzle->height; i++)
    {
        if(i != 0 && i % this->puzzle->width == 0)
        {
            current=0;
            amount += BOXLENGTH;
        }
        auto button = new Fl_Button((BOXLENGTH)*current+STARTPOINT, (STARTPOINT+amount), BOXLENGTH, BOXLENGTH, "");
        button->callback(cbAddNumber, this);
        this->colorPuzzleButton(button);

        int* index = new int;
        *index = i;

        this->buttonNumberMap[button] = index;
        current++;
    }
}

void PuzzleBoardWindow::showPuzzleButtonLabels()
{
    for (const auto &buttonNumberPair : this->buttonNumberMap)
    {
        const int x = this->puzzle->getXCoordinateFromPosition(*buttonNumberPair.second);
        const int y = this->puzzle->getYCoordinateFromPosition(*buttonNumberPair.second);
        int squareValue = this->puzzle->getSquareValue(x, y);

        const char* buttonLabel = squareValue == this->blankSquareValue ? "" : to_string(squareValue).c_str();
        buttonNumberPair.first->copy_label(buttonLabel);
        if (this->puzzle->isPuzzleDefinedPosition(x, y))
        {
            buttonNumberPair.first->labelfont(FL_BOLD);
        }
    }
}

void PuzzleBoardWindow::hidePuzzleButtonLabels()
{
    for (const auto &buttonNumberPair : this->buttonNumberMap)
    {
        buttonNumberPair.first->copy_label("");
    }
}

void PuzzleBoardWindow::colorPuzzleButton(Fl_Button* button)
{
    int cellColorId = this->userSettings->getUsersCellColorPreference();
    if (cellColorId > 0)
    {
        button->color(Fl_Color(cellColorId));
    }

    int labelColorId = this->userSettings->getUsersLabelColorPreference();
    if (labelColorId > 0)
    {
        button->labelcolor(Fl_Color(labelColorId));
    }
}

void PuzzleBoardWindow::resetTimer()
{
    this->timerTime = 0;
}

void PuzzleBoardWindow::cbAddNumber(Fl_Widget* widget, void* data)
{
    PuzzleBoardWindow* window = (PuzzleBoardWindow*) data;
    if (window->isPaused)
    {
        return;
    }

    Fl_Button* buttonPushed = (Fl_Button*) widget;
    const int buttonNumber = *(window->buttonNumberMap[buttonPushed]);

    int x = window->puzzle->getXCoordinateFromPosition(buttonNumber);
    int y = window->puzzle->getYCoordinateFromPosition(buttonNumber);

    if (window->puzzle->isPuzzleDefinedPosition(x, y))
    {
        return;
    }

    int userEnteredValue;
    try
    {
        userEnteredValue = window->getUsersAddNumberInput();
    }
    catch (invalid_argument)
    {
        fl_message("You can only enter a number.");
        return;
    }
    catch (runtime_error)
    {
        return;
    }

    if (userEnteredValue > window->puzzle->height * window->puzzle->width || userEnteredValue <= 0)
    {
        fl_message(("Enter a number between 1 and " + to_string(window->puzzle->height * window->puzzle->width)).c_str());
        return;
    }

    window->puzzle->setSquareValue(x, y, userEnteredValue);
    const char* buttonLabel = userEnteredValue == window->blankSquareValue ? "" : to_string(userEnteredValue).c_str();
    buttonPushed->copy_label(buttonLabel);
}

int PuzzleBoardWindow::getUsersAddNumberInput()
{
    GetUserInputWindow getUserInputWindow("Add a number.");
    getUserInputWindow.set_modal();
    getUserInputWindow.show();

    while (getUserInputWindow.shown())
    {
        Fl::wait();
    }

    if (getUserInputWindow.getWindowResult() == GetUserInputWindow::WindowResult::OK)
    {
        return stoi(getUserInputWindow.getUserInput());
    }
    throw runtime_error("No User Input.");
}

void PuzzleBoardWindow::cbEvaluatePuzzle(Fl_Widget* widget, void* data)
{
    PuzzleBoardWindow* puzzleWindow = (PuzzleBoardWindow*) data;
    if (puzzleWindow->isPaused)
    {
        return;
    }
    if (puzzleWindow->puzzle->evaluateGameBoard())
    {
        puzzleWindow->windowResult = PuzzleBoardWindow::WindowResult::WIN;
        puzzleWindow->hide();
    }
    else
    {
        fl_message("Puzzle is not quite correct, keep trying!");
    }
}

void PuzzleBoardWindow::cbResetPuzzleboard(Fl_Widget* widget, void* data)
{
    PuzzleBoardWindow* window = (PuzzleBoardWindow*) data;
    if (window->isPaused)
    {
        return;
    }
    delete window->puzzle;
    window->puzzle = window->puzzleParser.loadOriginalPuzzle(window->puzzleNumber);
    window->showPuzzleButtonLabels();
    window->resetTimer();
}

void PuzzleBoardWindow::cbLoadUserSave(Fl_Widget* widget, void* data)
{
    PuzzleBoardWindow* window = (PuzzleBoardWindow*) data;
    if (window->isPaused)
    {
        return;
    }
    PuzzleManager* newPuzzle = nullptr;
    try
    {
        newPuzzle = window->puzzleParser.loadUserPuzzle(window->puzzleNumber);
    }
    catch (invalid_argument)
    {
        fl_message("Could not find a save for this puzzle.");
        delete newPuzzle;
        return;
    }
    delete window->puzzle;
    *window->puzzle = *newPuzzle;
    delete newPuzzle;
    window->hidePuzzleButtonLabels();
    window->showPuzzleButtonLabels();
    window->resetTimer();
}

void PuzzleBoardWindow::cbSaveUserPuzzle(Fl_Widget* widget, void* data)
{
    PuzzleBoardWindow* window = (PuzzleBoardWindow*) data;
    if (window->isPaused)
    {
        return;
    }
    PuzzleManager* currentPuzzle = window->puzzle;
    window->puzzleParser.saveUserPuzzle(currentPuzzle, window->puzzleNumber);
}

void PuzzleBoardWindow::cbPauseGame(Fl_Widget* widget, void* data)
{
    PuzzleBoardWindow* window = (PuzzleBoardWindow*) data;
    window->isPaused = !(window->isPaused);
    const char* pauseButtonLabel = window->isPaused ? "Resume" : "Pause";
    window->pauseButton->copy_label(pauseButtonLabel);
    if (window->isPaused)
    {
        window->hidePuzzleButtonLabels();
    }
    else
    {
        window->showPuzzleButtonLabels();
    }
}

void PuzzleBoardWindow::cbTimer(void *data)
{
    PuzzleBoardWindow* window = (PuzzleBoardWindow*) data;
    Fl::repeat_timeout(1, cbTimer, data);
    if (window->isPaused)
    {
        return;
    }
    int currentTime = window->timerTime;
    window->timerOutput->value(to_string(currentTime).c_str());
    window->timerTime = currentTime + 1;
}

PuzzleBoardWindow::WindowResult PuzzleBoardWindow::getWindowResult()
{
    return this->windowResult;
}

int PuzzleBoardWindow::getTimerTime()
{
    return this->timerTime;
}

PuzzleBoardWindow::~PuzzleBoardWindow()
{
    for( const auto &buttonNumberPair : this->buttonNumberMap)
    {
        delete buttonNumberPair.first;
    }
    delete this->puzzleNumberLabel;
    delete this->puzzleNumberBox;
    delete this->timerLabel;
    delete this->puzzleNumberOutputTextDisplay;
    delete this->evaluatePuzzleButton;
    delete this->resetPuzzleButton;
    delete this->timerOutput;
    delete this->saveButton;
    delete this->loadButton;
    delete this->pauseButton;
    delete this->puzzle;
    delete this->userSettings;
}
}
