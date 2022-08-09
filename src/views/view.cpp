#include "views/view.hpp"

#include <ncurses.h>

#include "manager/view-manager.hpp"
// TODO(gio): fixa gli include di questo file, segui la filosofia: "includi quello che usi"
// https://google.github.io/styleguide/cppguide.html#Include_What_You_Use

namespace views
{

    bool View::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view,bool changedView) {return false;}

    void View::handleInput(char input) {}

    View::View(Position pos, Size size) : winSize(size), winPosition(pos)
    {
        window = newwin(size.riga, size.colonna, pos.riga, pos.colonna);
    }

    View::~View()
    {
        delwin(window);
    }

    void View::render(bool force)
    {
        if (force)
        {
            erase();
            touchwin(window);
        }
        wrefresh(window);
    }

}; // namespace views
