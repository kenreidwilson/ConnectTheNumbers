#include "GameMainWindow.h"
#include "PuzzleboardWindow.h"
#include "ScoreboardWindow.h"
#include "UserPreferencesWindow.h"

namespace View
{
GameMainWindow::GameMainWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    this->begin();

    this->gameTitleLabel = new Fl_Output((width / 2) + 75, 50, 0, 0, "Connect the Numbers");

    initializePuzzleButtons();
    this->scoreboardButton = new Fl_Button(width/3 - 5, 380, 100, 30, "Score Board");
    this->scoreboardButton->callback(cbShowScoreBoard, this);
    this->setColorButton = new Fl_Button(width/3 - 5, 420, 100, 30, "Set Color");
    this->setColorButton->callback(cbSetUserColorPreference, this);

    this->userSettings = new UserSettings();
    this->scoreboard = new Scoreboard();

    this->end();
}

void GameMainWindow::initializePuzzleButtons()
{
    int firstButtonColumnX = 50;
    int secondButtonColumnX = 170;
    int buttonMinimumPadding = 30;
    int buttonPadding = 50;

    for (int i = 1; i < this->numberOfPuzzles + 1; i++)
    {
        string* buttonLabel = new string("Puzzle " + to_string(i));
        this->buttonLabels.push_back(buttonLabel);

        int x = i > this->numberOfPuzzles/2 ? secondButtonColumnX : firstButtonColumnX;
        int y = i > this->numberOfPuzzles/2 ? (i - this->numberOfPuzzles/2) * buttonPadding + buttonMinimumPadding : i * buttonPadding + buttonMinimumPadding;

        int* index = new int;
        *index = i;

        Fl_Button* puzzleButton = new Fl_Button(x, y, 70, 30, buttonLabel->c_str());
        puzzleButton->callback(cbOpenPuzzle, this);
        this->buttonNumberMap[puzzleButton] = index;
    }
}

void GameMainWindow::cbOpenPuzzle(Fl_Widget* widget, void* data)
{
    GameMainWindow* window = (GameMainWindow*) data;
    int puzzleNumber = *(window->buttonNumberMap[(Fl_Button*) widget]);

    PuzzleBoardWindow* puzzleWindow;
    try
    {
        puzzleWindow = new PuzzleBoardWindow(puzzleNumber, window->userSettings);
    }
    catch (invalid_argument error)
    {
        fl_message("Failed to load the puzzle.");
        return;
    }

    string puzzleNumberLabel = "Puzzle #" + to_string(puzzleNumber);
    puzzleWindow->set_modal();
    puzzleWindow->show();
    while (puzzleWindow->shown())
    {
        Fl::wait();
    }
    if (puzzleWindow->getWindowResult() == PuzzleBoardWindow::WindowResult::WIN)
    {
        window->handlePlayerWin((Fl_Button*) widget, puzzleWindow->getTimerTime());
    }
}

void GameMainWindow::handlePlayerWin(Fl_Button* senderButton, int timerTime)
{
    int puzzleNumber = *(this->buttonNumberMap[senderButton]);
    try
    {
        this->scoreboard->addScore(getPlayerName(), puzzleNumber, timerTime);
    }
    catch (runtime_error)
    {
        fl_message("Your score was not recorded.");
    }

    int nextPuzzleNumber = puzzleNumber + 1;
    Fl_Button* nextPuzzleButton = nullptr;
    for (const auto &buttonNumberPair : this->buttonNumberMap)
    {
        if (nextPuzzleNumber == *(buttonNumberPair.second))
        {
            nextPuzzleButton = buttonNumberPair.first;
        }
    }

    if (nextPuzzleButton != nullptr)
    {
        GameMainWindow::cbOpenPuzzle(nextPuzzleButton, this);
    }
    else
    {
        fl_message("Congratulations you completed all puzzles.");
    }
}

string GameMainWindow::getPlayerName()
{
    GetUserInputWindow* winnerWindow = new GetUserInputWindow("You Won!");
    winnerWindow->set_modal();
    winnerWindow->show();

    while(winnerWindow->shown())
    {
            Fl::wait();
    }

    string playerName = winnerWindow->getUserInput();

    if (playerName == "")
    {
        throw runtime_error("player did not provide a name.");
    }

    return playerName;
}

void GameMainWindow::cbShowScoreBoard(Fl_Widget* widget, void* data)
{
    GameMainWindow* gameMainWindow = (GameMainWindow*) data;
    ScoreboardWindow* scoreboardWindow = new ScoreboardWindow(gameMainWindow->scoreboard);
    scoreboardWindow->set_modal();
    scoreboardWindow->show();

    while (scoreboardWindow->shown())
    {
        Fl::wait();
    }
}

void GameMainWindow::cbSetUserColorPreference(Fl_Widget* widget, void* data)
{
    GameMainWindow* gameMainWindow = (GameMainWindow*) data;

    UserPreferencesWindow* userPreferencesWindow = new UserPreferencesWindow(gameMainWindow->userSettings);
    userPreferencesWindow->set_modal();
    userPreferencesWindow->show();

    while (userPreferencesWindow->shown())
    {
        Fl::wait();
    }
    gameMainWindow->userSettings->saveSettings();
}

GameMainWindow::~GameMainWindow()
{
    for (const auto &buttonNumberPair: this->buttonNumberMap)
    {
        delete buttonNumberPair.first;
        delete buttonNumberPair.second;
    }
    for (int i = 0; i < this->numberOfPuzzles; i++)
    {
        delete this->buttonLabels[i];
    }
    delete this->setColorButton;
    delete this->scoreboardButton;
    delete this->gameTitleLabel;
    delete this->userSettings;
    delete this->scoreboard;
}
}

