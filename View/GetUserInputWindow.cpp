#include "GetUserInputWindow.h"

namespace View
{
GetUserInputWindow::GetUserInputWindow(const char* title) : Fl_Window(300, 200, title)
{
    this->buttonInvoked = WindowResult::NONE;
    begin();
    this->okButton = new Fl_Button(80, 150, 70, 30, "OK");
    this->okButton->callback(cbOk, this);
    this->cancelButton = new Fl_Button(160,150,70,30,"Cancel");
    this->cancelButton->callback(cbCancel, this);
    this->userInputInput = new Fl_Input(100, 50, 100, 50,"");
    Fl::focus(this->userInputInput);
    end();
}

GetUserInputWindow::~GetUserInputWindow()
{
    delete this->cancelButton;
    delete this->okButton;
    delete this->userInputInput;
}

void GetUserInputWindow::cbOk(Fl_Widget* widget, void* data)
{
    GetUserInputWindow* window = (GetUserInputWindow*)data;
    window->setWindowResult(GetUserInputWindow::OK);
    window->okHandler();
}


void GetUserInputWindow::cbCancel(Fl_Widget* widget, void* data)
{
    GetUserInputWindow* window = (GetUserInputWindow*)data;
    window->setWindowResult(GetUserInputWindow::CANCEL);
    window->cancelHandler();
}

GetUserInputWindow::WindowResult GetUserInputWindow::setWindowResult(GetUserInputWindow::WindowResult result)
{
    this->buttonInvoked = result;
}

void GetUserInputWindow::okHandler()
{
    try
    {
        this->userInput = this->userInputInput->value();
        this->hide();
    }
    catch (const char* message)
    {
        fl_message("%s", message);
    }
}
void GetUserInputWindow::cancelHandler()
{

    this->userInput = "";
    this->hide();
}

GetUserInputWindow::WindowResult GetUserInputWindow::getWindowResult()
{
    return this->buttonInvoked;
}

string GetUserInputWindow::getUserInput() const
{
    return this->userInput;
}

}
