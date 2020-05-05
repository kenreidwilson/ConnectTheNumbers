#include "UserPreferencesWindow.h"

namespace View
{
UserPreferencesWindow::UserPreferencesWindow(UserSettings* settings) : Fl_Window(300, 200, "User Preferences")
{
    this->begin();
    this->userSettings = settings;
    this->cellColorChoice = new Fl_Choice(100, 40, 120, 30, "Cell Color");
    this->cellColorChoice->callback(cbCellColorChoiceSelected, this);
    this->labelColorChoice = new Fl_Choice(100, 90, 120, 30, "Label Color");
    this->labelColorChoice->callback(cbLabelColorChoiceSelected, this);
    this->doneButton = new Fl_Button(120, 150, 70, 30, "Done");
    this->doneButton->callback(cbDone, this);
    this->colorChoices = {
        {"Default", -1},
        {"Red",88},
        {"White", 255},
        {"Black", 56},
        {"Green", 63},
        {"Yellow", 95},
        {"Blue", 216},
        {"Magenta", 248},
        {"Cyan", 223}
    };
    initializeChoices();
    this->end();
}

UserPreferencesWindow::~UserPreferencesWindow()
{
    delete this->cellColorChoice;
    delete this->labelColorChoice;
    delete this->doneButton;
}

void UserPreferencesWindow::initializeChoices()
{
    for (const auto &colorIdPair : this->colorChoices)
    {
        this->cellColorChoice->add(colorIdPair.first.c_str());
        this->labelColorChoice->add(colorIdPair.first.c_str());
    }
}

void UserPreferencesWindow::cbDone(Fl_Widget* widget, void* data)
{
    UserPreferencesWindow* window = (UserPreferencesWindow*) data;
    window->hide();
}

void UserPreferencesWindow::cbCellColorChoiceSelected(Fl_Widget* widget, void* data)
{
    Fl_Choice* chosenChoice = (Fl_Choice*) widget;
    UserPreferencesWindow* window = (UserPreferencesWindow*) data;
    int colorId = window->colorChoices[string(chosenChoice->text())];
    window->userSettings->setUsersCellColorPreference(colorId);
}

void UserPreferencesWindow::cbLabelColorChoiceSelected(Fl_Widget* widget, void* data)
{
    Fl_Choice* chosenChoice = (Fl_Choice*) widget;
    UserPreferencesWindow* window = (UserPreferencesWindow*) data;
    int colorId = window->colorChoices[string(chosenChoice->text())];
    window->userSettings->setUsersLabelColorPreference(colorId);
}

}
