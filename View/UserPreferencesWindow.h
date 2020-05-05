#ifndef USERPREFERENCESWINDOW_H
#define USERPREFERENCESWINDOW_H

#include <Fl/Fl_Input.H>
#include <Fl/Fl_Choice.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <Fl/fl_ask.H>

#include "UserSettings.h"
using namespace Model;

namespace View
{
/**
* A window that allows a user to choice their preferences.
*/
class UserPreferencesWindow: public Fl_Window
{
    public:
        /**
        * Constucts a UserPreferencesWindow.
        *
        * @param settings A pointer to the user's UserSettings object.
        */
        UserPreferencesWindow(UserSettings* settings);

        /**
        * Destructs a UserPreferencesWindow.
        */
        virtual ~UserPreferencesWindow();

    private:
        UserSettings* userSettings;
        map<string, int> colorChoices;

        Fl_Choice* cellColorChoice;
        Fl_Choice* labelColorChoice;
        Fl_Button* doneButton;
        void initializeChoices();
        static void cbDone(Fl_Widget* widget, void* data);
        static void cbCellColorChoiceSelected(Fl_Widget* widget, void* data);
        static void cbLabelColorChoiceSelected(Fl_Widget* widget, void* data);
};
}
#endif // USERPREFERENCESWINDOW_H
