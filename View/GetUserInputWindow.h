#ifndef GETUSERINPUTWINDOW_H
#define GETUSERINPUTWINDOW_H_H

#include <FL/Fl.H>
#include <Fl/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <Fl/fl_ask.H>

#include <string>
using namespace std;

namespace View
{
/**
* A window that gets feedback from the user.
*/
class GetUserInputWindow: public Fl_Window
{
public:
    /**
    * Constructs a GetUserInputWindow.
    *
    * @param title The title of the window.
    */
    GetUserInputWindow(const char* title);

    /**
    * Destructs a GetUserInputWindow.
    */
    virtual ~GetUserInputWindow();

    /**
    * Enums describing the ending result of a GetUserInputWindow.
    */
    enum WindowResult {OK, CANCEL, NONE};

    /**
    * Returns the result of the GetUserInputWindow.
    *
    * @return the result of the GetUserInputWindow.
    */
    GetUserInputWindow::WindowResult getWindowResult();

    /**
    * Returns the user's input.
    *
    * @return the user's input.
    */
    string getUserInput() const;

private:
    Fl_Button* okButton;
    Fl_Button* cancelButton;
    Fl_Input *userInputInput;
    WindowResult buttonInvoked;
    string userInput;

    void okHandler();
    void cancelHandler();
    static void cbOk(Fl_Widget* widget, void* data);
    static void cbCancel(Fl_Widget* widget, void* data);
    GetUserInputWindow::WindowResult setWindowResult(GetUserInputWindow::WindowResult result);
};

}

#endif // SELECTEDPIECEWINDOW_H
