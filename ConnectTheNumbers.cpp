#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "View/GameMainWindow.h"
using namespace View;

int main (int argc, char ** argv)
{
    GameMainWindow game(300, 480, "Connect the Numbers");
    game.show();

    return(Fl::run());
}
