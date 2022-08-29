#include "views/view.hpp"

#include <ncurses.h>

#include "manager/view-manager.hpp"
// TODO(gio): fixa gli include di questo file, segui la filosofia: "includi quello che usi"
// https://google.github.io/styleguide/cppguide.html#Include_What_You_Use

namespace views {

    View::View(Position pos, Size size)
        : winSize(size), winPosition(pos), name_("View") {
        window = newwin(size.riga, size.colonna, pos.riga, pos.colonna);
    }

    View::~View() {
        delwin(window);
    }

    void View::clearWindow() {
        erase();
        refresh();
        touchwin(window);
    }

    void View::render(bool force) {
        if (force) {
            clearWindow();
        }
        wrefresh(window);
    }

    const char *View::getName() {
        return name_;
    }

};  // namespace views
