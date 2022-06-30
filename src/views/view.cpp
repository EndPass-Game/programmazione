#include "views/view.hpp"

namespace views
{

    bool View::handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView) {return false;}

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
            clear();
            touchwin(window);
        }
        wrefresh(window);
    }

}; // namespace views
